
template<typename T>
T operator*(const std::vector<T> &a, const std::vector<T> &b)
{

    T result = 0;
    for (int i = 0; i < a.size(); i++)
    {
        result += a[i] * b[i];
    }
    return result;
}

template <typename T>
std::vector<T> operator/(const std::vector<T> &b, const T &alpha)
{
    std::vector<T> result(b.size());
    for (int i = 0; i < result.size(); i++)
    {
        result[i] = b[i] / alpha;
    }
    return result;
}

template<typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> result(a.size());
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] - b[i];
    }

    return result;
}
