#ifndef LCS_H
#define LCS_H

#include <QString>
#include <vector>
#include <QStringList>

class Lcs
{
public:
    Lcs();
    void test();
    bool initiate(const QString &text1, const QString &text2);
    int getRelationTypeLeft(int idxLeft);
    int getRelationTypeRight(int idxRight);
    int getRelationIndexLeft(int idxLeft);
    int getRelationIndexRight(int idxRight);
    bool incrementLevelFromLeft(int idxLeft);
    bool incrementLevelFromRight(int idxRight);
    bool decrementLevel();
    bool changeRelation(int relationType, int idxLeft, int idxRight);

    static const int NO_RELATIVES = -1;

    static const int UNMATCHED = 0;
    static const int CHANGED = 1;
    static const int MOVED = 2;
    static const int MATCHED = 3;

    struct UniniciatedException : public std::exception{
        const char * what () const throw ();};
    struct DecrementZeroLevelException : public std::exception{
        const char * what () const throw ();};
    struct IncrementMaxLevelException : public std::exception{
        const char * what () const throw ();};
    struct ChangingMaxLevelException : public std::exception{
        const char * what () const throw ();};
    struct IncrementingEmptySideException : public std::exception{
        const char * what () const throw ();};

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

    enum State{UNINICIATED, INICIATED} state;

    uint currentLevel;
    relation *currentLeftParent;
    relation *currentRightParent;

    std::vector<relation> levelZeroRelations1;
    std::vector<relation> levelZeroRelations2;

    void initRelations(const QString &text, std::vector<relation> &rel,
                       uint level, relation *partent);
    int** getLcsMatrix();
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
    int checkRelations(const QString &text1, const QString &text2, uint level,
                       std::vector<relation> &rel1,
                       std::vector<relation> &rel2);
    void clearRelation(relation &rel);
    QStringList separate(const QString &text, int level);
    int getContainedSize(const QString &container,
                              QStringList::const_iterator iter,
                              QStringList::const_iterator end);

};


#endif // LCS_H
