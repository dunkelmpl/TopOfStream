# TopOfStream

Task: implement template class TopOfStream<TKey, TValue> with following functionality:

1. Constructor gets limit of stream size
2. Method "add" gets key and value of types TKey and TValue respectively and performs adding item to the stream
3. Implemented class should always store up to <limit> number of top (biggest) items
4. Class should provide functionality to traverse all its currently stored items, using iterators begin() and end()
