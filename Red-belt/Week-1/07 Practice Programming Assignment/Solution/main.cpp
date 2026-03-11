#include "test_runner.h"

using namespace std;

template <typename T>
class Table {
private:
    vector<vector<T>> data;
public:
    Table(size_t rows_num, size_t columns_num) {
        Resize(rows_num, columns_num);
    }

    void Resize(size_t rows_num, size_t columns_num) {
        data.resize(rows_num);
        for (auto& item : data) {
            item.resize(columns_num);
        }
    }

    pair<size_t, size_t> Size() const {
        return {data.size(), data[0].size()};
    }

    const vector<T>& operator[](size_t index) const {
        return data[index];
    }

    vector<T>& operator[](size_t index) {
        return data[index];
    }
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);

    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);

    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);

    return 0;
}
