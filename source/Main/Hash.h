#pragma once

template <class K, class V>
class Hash
{
public:
  Hash()
  {
    index_count = 0;
    keys = new K[index_count];
    values = new V[index_count];
  }

  ~Hash()
  {
    delete[] keys;
    delete[] values;
  }

  V value(K key, V _default = V()) const
  {
    int index = key_index(key);
    if (index < 0)
      return _default;
    return values[index];
  }

  K key(V value, K _default = K()) const
  {
    int index = value_index(value);
    if (index < 0)
      return _default;
    return keys[index];
  }

  bool contains(K key) const
  {
    return key_index(key) >= 0;
  }

  int key_index(K key) const
  {
    for (int index = 0; index < index_count; index++)
      if (keys[index] == key)
        return index;
    return -1;
  }

  int value_index(V value) const
  {
    for (int index = 0; index < index_count; index++)
      if (values[index] == value)
        return index;
    return -1;
  }

  void insert(K key, V value)
  {
    int index = key_index(key);
    if (index < 0)
      index = create_index();
    keys[index] = key;
    values[index] = value;
  }

  void remove_key(K key)
  {
    int index = key_index(key);
    if (index >= 0)
      remove_index(index);
  }

  int count() const
  {
    return index_count;
  }

  int size() const
  {
    return index_count;
  }

private:
  int create_index()
  {
    K *temp_keys = nullptr;
    temp_keys = new K[index_count + 1];
    for (int index = 0; index < index_count; index++)
      temp_keys[index] = keys[index];

    V *temp_values = nullptr;
    temp_values = new V[index_count + 1];
    for (int index = 0; index < index_count; index++)
      temp_values[index] = values[index];

    index_count++;

    delete[] keys;
    delete[] values;

    keys = temp_keys;
    values = temp_values;

    return index_count - 1;
  }

  void remove_index(int r_index)
  {
    K *temp_keys = nullptr;
    temp_keys = new K[index_count - 1];
    for (int index = 0, real = 0; index < index_count; index++)
      if (index != r_index)
      {
        temp_keys[real] = keys[index];
        real++;
      }

    V *temp_values = nullptr;
    temp_values = new V[index_count - 1];
    for (int index = 0, real = 0; index < index_count; index++)
      if (index != r_index)
      {
        temp_values[real] = values[index];
        real++;
      }

    index_count--;

    delete[] keys;
    delete[] values;

    keys = temp_keys;
    values = temp_values;
  }

  int index_count;
  K *keys;
  V *values;
};
