# LeetCode-925-LongPressedName
## 题目描述：

## 题目讲解：

---
## 代码实现：
·  int IsLongPressedName(const char *name, const char *typed)
{
    int nIndex = 0;
    int tIndex = 0;
    while (name[nIndex] != '\0') {
        if (name[nIndex] != name[nIndex + 1]) {
            if (name[nIndex] != typed[tIndex]) {
                return 0;
            }
            while (typed[tIndex] == typed[tIndex + 1]) {
                tIndex++;
            }
        } else if (name[nIndex] != typed[tIndex]) {
            return 0;
        }
        nIndex++;
        tIndex++;
    }
    if (typed[tIndex] != '\0') {
        return 0;
    }
    return 1;
}·
