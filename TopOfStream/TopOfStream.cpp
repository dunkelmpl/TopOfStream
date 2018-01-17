#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

/**
* Task: implement template class TopOfStream<TKey, TValue> with following
* functionality:
*
* 1. Constructor gets limit of stream size
* 2. Method "add" gets key and value of types TKey and TValue respectively and performs adding item to
*    the stream
* 3. Implemented class should always store up to <limit> number of top (biggest) items
* 4. Class should provide functionality to traverse all its currently stored items,
*    using iterators begin() and end()
*/
template <class TKey, class TValue>
class TopOfStream
{
    typedef pair<TKey, TValue> TPair;

    struct Comparator
    {
        bool operator()(const TPair& item1, const TPair& item2) const {
            return item1.first > item2.first;
        }
    };

public:
    TopOfStream(size_t limit) : limit(limit), storage(0)
    {
        if (limit == 0) {
            throw invalid_argument("Limit cannot be zero");
        }
    }

    void add(TKey key, TValue value)
    {
        TPair newItem = make_pair(key, value);

        if (storage.size() >= limit) {
            // As soon as we reached limit, we organize storage as min heap 
            if (storage.size() == limit) {
                make_heap(storage.begin(), storage.end(), Comparator());
            }

            // If lowest element in storage is smaller than new key,
            // then we need to remove it (first/lowest element) and insert new
            if (storage[0].first < key) {
                if (storage.size() > 1) {
                    // pop min item to the latest element and replace it with new item
                    pop_heap(storage.begin(), storage.end(), Comparator());
                    storage[storage.size() - 1] = newItem;

                    // now restore min heap (via sifting up)
                    push_heap(storage.begin(), storage.end(), Comparator());
                } else {
                    // If there's only one element, let's just replace it
                    storage[0] = newItem;
                }
            }
        } else {
            // Unless we reached limit, we just add item to the storage.
            storage.push_back(newItem);
        }
    }

    using const_iterator = typename vector<TPair>::const_iterator;

public:
    const_iterator begin() const
    {
        return storage.begin();
    }

    const_iterator end() const
    {
        return storage.end();
    }

private:
    size_t limit;
    vector<TPair> storage;
};

int main()
{
    const int limit = 6;

    TopOfStream<float, string> tos(limit);
    tos.add(1.2f, "test1.2");
    tos.add(3.2f, "test3.2");
    tos.add(10.5f, "test10.5");
    tos.add(4.f, "test4");
    tos.add(2.f, "test2");
    tos.add(3.2f, "test3.2(2)");
    tos.add(3.3f, "test3.3");
    tos.add(8.f, "test8");

    cout << "Top of stream with limit " << limit << ":\n";

    for (TopOfStream<float, string>::const_iterator it = tos.begin(); it != tos.end(); it++) {
        cout << (*it).first << ": " << (*it).second << "\n";
    }

    cout << endl;

    return 0;
}