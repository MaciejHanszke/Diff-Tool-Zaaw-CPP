#ifndef LCS_H
#define LCS_H

#include <QString>
#include <vector>
#include <QStringList>

#define NO_RELATIVES -1

#define UNMATCHED 0
#define CHANGED 1
#define MOVED 2
#define MATCHED 3

class Lcs
{
public:
    Lcs();
    int** getLcsMatrix();
    void test();


private:

    struct relation
    {
        relation();
        ~relation();
        int typeOfReleation;
        int releativesIndex;
        std::vector<relation> children;
        relation* parent;
    };


    std::vector<relation> levelZeroRelations1;
    std::vector<relation> levelZeroRelations2;

    bool createLcsMatrix(const QString &text1, const QString &text2);
    int getNumberOfLines(const QString &text);
    int getNumberOfLines(const QStringList &textList);
    int** getLcsMatrix(const QStringList &list1, const QStringList &list2);
    void backtrackAndMark(int** lcsMatrix, std::vector<relation> &rel1,
                          std::vector<relation> &rel2,
                          const QStringList &list1, const QStringList &list2);
    int markMoved(std::vector<relation> &rel1, std::vector<relation> &rel2,
                   const QStringList &list1, const QStringList &list2);
    int checkListsRelations(const QStringList &list1, const QStringList &list2,
                            std::vector<relation> &rel1, std::vector<relation> &rel2);
    int checkRelations(const QString &text1, const QString &text2, int level,
                       std::vector<relation> &rel1,
                       std::vector<relation> &rel2);
    void clearRelation(relation &rel);
    QStringList separate(const QString &text, int level);
    int getContainedSize(const QString &container,
                              QStringList::const_iterator iter,
                              QStringList::const_iterator end);

};


#endif // LCS_H
