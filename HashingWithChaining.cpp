#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using std::string;
using std::vector;
using std::cin;
using std::list;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    vector<list<string> > hashTable;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count)
    {
    	hashTable.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
        {
            cin >> query.s;
        }
        else
        {
            cin >> query.ind;
        }
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    bool hasKey(const Query& query, size_t hashcode)
    {
        list<string> tempList = hashTable[hashcode];
        for (std::list<string>::iterator it = tempList.begin(); it != tempList.end(); ++it)
        {
            if (*it == query.s)
            {
                return true;
            }
        }
        return false;

    }

    void processWithHashChain(const Query& query)
    {
        if (query.type == "check")
        {
            if (!hashTable[query.ind].empty())
            {
                for (std::list<string>::iterator it = hashTable[query.ind].begin(); it != hashTable[query.ind].end(); ++it)
                {
                    std::cout << *it << " ";
                }
            }
            std::cout << "\n";
        }
        else
        {
            size_t queryHash = hash_func(query.s);
            if (query.type == "add")
            {
                if (!hasKey(query, queryHash))
                {
                    hashTable[queryHash].push_front(query.s);
                }
            }
            else if (query.type == "find")
            {
                writeSearchResult(hasKey(query, queryHash));
            }
            else if (query.type == "del")
            {
                for (std::list<string>::iterator it = hashTable[queryHash].begin(); it != hashTable[queryHash].end(); ++it)
                {
                    if (*it == query.s)
                    {
                        hashTable[queryHash].erase(it);
                        break;
                    }
                }
            }
        }

    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            //processQuery(readQuery());
            processWithHashChain(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
