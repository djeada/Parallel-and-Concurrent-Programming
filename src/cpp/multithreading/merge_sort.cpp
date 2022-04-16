#include <iostream>
#include <thread>
#include <vector>

void merge(std::vector<int> &v, int left, int mid, int right) {
  std::vector<int> temp(right - left + 1);
  int i = left, j = mid + 1, k = 0;
  while (i <= mid && j <= right) {
    if (v[i] < v[j])
      temp[k++] = v[i++];
    else
      temp[k++] = v[j++];
  }
  while (i <= mid)
    temp[k++] = v[i++];
  while (j <= right)
    temp[k++] = v[j++];
  for (int i = 0; i < temp.size(); i++)
    v[left + i] = temp[i];
}

void merge_sort(std::vector<int> &v, int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    merge_sort(v, left, mid);
    merge_sort(v, mid + 1, right);
    merge(v, left, mid, right);
  }
}

void merge_sort_thread(std::vector<int> &v, int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    std::thread t1(merge_sort_thread, std::ref(v), left, mid);
    std::thread t2(merge_sort_thread, std::ref(v), mid + 1, right);
    t1.join();
    t2.join();
    merge(v, left, mid, right);
  }
}

int main() {
  std::vector<int> v = {4, 2, 1, 5, 3, 6, 7, 8, 9, 0};
  merge_sort_thread(v, 0, v.size() - 1);
  for (const auto elem : v)
    std::cout << elem << " ";
  std::cout << std::endl;
  return 0;
}
