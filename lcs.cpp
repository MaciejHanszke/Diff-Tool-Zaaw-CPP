#include "lcs.h"


#include <algorithm>
#include <array>
#include <cstddef>
#include <cmath>

#include <QFile>
#include <QTextStream>
#include <iostream>



namespace  {
    const QStringList PARAGRAPH_SEPARATORS = {"\n"};
    const QStringList SENTENCE_SEPARATORS = {". ", "? ","! "};
    const QStringList WORD_SEPARATORS = {" "};
    const std::array<QStringList, 3> SEPARATORS = {PARAGRAPH_SEPARATORS,
                                                 SENTENCE_SEPARATORS,
                                                 WORD_SEPARATORS};
}


Lcs::Lcs()
{
    currentLevel=0;
    currentLeftParent = nullptr;
    currentRightParent = nullptr;
}

//   #####################################
//   ################ api ################
//   #####################################

void Lcs::initiate(const QString &text1, const QString &text2){
    checkRelations(text1, text2, 0, levelZeroRelations1, levelZeroRelations2);
    return;
}

int Lcs::getRelationTypeLeft(int idxLeft){
    if(!currentLevel){
        return levelZeroRelations1[idxLeft].typeOfReleation;
    } else {
        return currentLeftParent->children[idxLeft].typeOfReleation;
    }
    return -1;
}

int Lcs::getRelationTypeRight(int idxRight){
    if(!currentLevel){
        return levelZeroRelations2[idxRight].typeOfReleation;
    } else {
        return currentRightParent->children[idxRight].typeOfReleation;
    }
    return -1;
}

bool Lcs::incrementLevelFromLeft(int idxLeft){
    if(currentLevel==SEPARATORS.size()-1){
        return false;
    }
    if(!currentLevel){
        currentLeftParent = &levelZeroRelations1[idxLeft];
    } else {
        currentLeftParent = &currentLeftParent->children[idxLeft];
    }
    currentRightParent = &levelZeroRelations2[currentLeftParent->releativesIndex];
    ++currentLevel;
    return true;
}

bool Lcs::incrementLevelFromRight(int idxRight){
    if(currentLevel==SEPARATORS.size()-1){
        return false;
    }
    if(!currentLevel){
        currentRightParent = &levelZeroRelations2[idxRight];
    } else {
        currentRightParent = &currentRightParent->children[idxRight];
    }
    currentLeftParent = &levelZeroRelations1[currentRightParent->releativesIndex];
    ++currentLevel;
    return true;
}

bool Lcs::decrementLevel(){
    if(!currentLevel){
        return false;
    }
    currentLeftParent = currentLeftParent->parent;
    currentRightParent = currentRightParent->parent;
    --currentLevel;
    return true;
}

//   #####################################
//   ############## end api ##############
//   #####################################


void Lcs::test(){
    std::cout<<"lol"<<std::endl;
    QString text1, text2;
    QFile graphFile("one");
    if (!graphFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cout<<"lol1"<<std::endl;
        return;}
    QTextStream in(&graphFile);
    text1=in.readAll();
    graphFile.close();
    QFile file("two");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cout<<"lol2"<<std::endl;
        return;}
    QTextStream in2(&file);
    text2=in2.readAll();
    file.close();

    checkRelations(text1, text2, 0, levelZeroRelations1, levelZeroRelations2);

    for(int i=0; i<levelZeroRelations1.size();++i){
        std::cout<<levelZeroRelations1[i].typeOfReleation<<":"
                <<levelZeroRelations1[i].releativesIndex<<std::endl;
    }
    return;
}

int** Lcs::getLcsMatrix(const QStringList &list1, const QStringList &list2){
    int len1 = getNumberOfLines(list1);
    int len2 = getNumberOfLines(list2);

    for(int i=0; i<len1;++i){
        std::cout<<list1[i].toStdString()<<std::endl;
    }
    for(int j=0; j<len2;++j){
        std::cout<<list2[j].toStdString()<<std::endl;
    }
    //initialize size of lcs lengh matrix
    //matrix is initialized with zeros
    int** lcsMatrix = new int*[len1+1];
    for(int i=0; i<=len1; ++i){
        lcsMatrix[i] = new int[len2+1];
        lcsMatrix[i][len2] = 0;
    }
    for(int j=0; j<len2; ++j){
        lcsMatrix[len1][j]=0;
    }
    //fill lcs lengh matrix and mark matches
    for(int i=0; i<len1; ++i){
        for(int j=0; j<len2; ++j){
            int prev_i = (i ? i-1:len1);
            int prev_j = (j ? j-1:len2);
            if(!QString::compare(list1[i],list2[j], Qt::CaseSensitive)){
                lcsMatrix[i][j] = 1 + lcsMatrix[prev_i][prev_j];
            } else {
                lcsMatrix[i][j] = std::max(lcsMatrix[i][prev_j], lcsMatrix[prev_i][j]);
            }
        }
    }
    for(int i=0; i<len1;++i){
        for(int j=0; j<len2;++j){
            std::cout<<lcsMatrix[i][j];
        }
        std::cout<<std::endl;
    }
    return lcsMatrix;
}

void Lcs::backtrackAndMark(int** lcsMatrix, std::vector<relation> &rel1, std::vector<relation> &rel2,
                           const QStringList &list1, const QStringList &list2){
    int len1 = getNumberOfLines(list1);
    int len2 = getNumberOfLines(list2);
    int i = len1-1;
    int j = len2-1;

    while(i > -1 && j>-1){
        int prev_i = (i ? i-1:len1);
        int prev_j = (j ? j-1:len2);
        if(!QString::compare(list1[i],list2[j], Qt::CaseSensitive)){
            rel1[i].typeOfReleation = MATCHED;
            rel1[i].releativesIndex = j;
            rel2[j].typeOfReleation = MATCHED;
            rel2[j].releativesIndex = i;
            --i; --j;
        }else if(lcsMatrix[prev_i][j]<lcsMatrix[i][prev_j]){
            --j;
        }else{
            --i;
        }
    }
}

int Lcs::markMoved(std::vector<relation> &rel1, std::vector<relation> &rel2,
                    const QStringList &list1, const QStringList &list2){
    int len1 = getNumberOfLines(list1);
    int len2 = getNumberOfLines(list2);
    int moved = 0;
    for(int i=0; i<len1; ++i){
        if(rel1[i].typeOfReleation==MATCHED){
            continue;
        }
        for(int j=0; j<len2; ++j){
            if(rel2[j].typeOfReleation==MATCHED){
                continue;
            } else if(!QString::compare(list1[i],list2[j], Qt::CaseSensitive)){
                rel1[i].typeOfReleation = MOVED;
                rel1[i].releativesIndex = j;
                rel2[j].typeOfReleation = MOVED;
                rel2[j].releativesIndex = i;
                ++moved;
            }
        }
    }
    return moved;
}

Lcs::relation::relation(){
    typeOfReleation = UNMATCHED;
    releativesIndex = NO_RELATIVES;
    parent = nullptr;
}

Lcs::relation::~relation(){
}

int Lcs::checkRelations(const QString &text1, const QString &text2, int level,
                        std::vector<relation> &rel1, std::vector<relation> &rel2,
                        relation *parent1, relation *parent2){
    int decision = UNMATCHED;
    std::cout<<level<<std::endl;
    //split texts into lists
    QStringList list1 = separate(text1, level);
    QStringList list2 = separate(text2, level);

    int len1 = getNumberOfLines(list1);
    int len2 = getNumberOfLines(list2);


    int matched = checkListsRelations(list1, list2, rel1, rel2, parent1, parent2);
    int moved = markMoved(rel1, rel2, list1, list2);

    if(level==SEPARATORS.size()-1){
        if(matched+moved >= 1+std::floor(len1*0.4)){
            return CHANGED;
        }
    } else {
        int marked = 0;
        for(int i=0; i<len1; ++i){
            if(rel1[i].typeOfReleation>UNMATCHED){
                continue;
            }else{
                for(int j=0; j<len2; ++j){
                if(rel2[j].typeOfReleation>UNMATCHED){
                    continue;
                } else {
                int decision_in = checkRelations(list1[i], list2[j], level+1,
                                                 rel1[i].children, rel2[j].children,

                                                 &rel1[i], &rel2[j]);
                if(decision_in>UNMATCHED){
                    ++marked;
                    rel1[i].typeOfReleation = CHANGED;
                    rel1[i].releativesIndex = j;
                    rel2[j].typeOfReleation = CHANGED;
                    rel2[j].releativesIndex = i;
                    break;
                } else {
                    clearRelation(rel1[i]);
                    clearRelation(rel2[j]);
                }}
            }}
        }
        std::cout<<"fuck   "<<matched+moved+std::floor(marked*0.75)<<std::endl;
        std::cout<<"fuck   "<<std::floor(len1*0.8)<<":"<<len1<<std::endl;
        if(matched+moved+std::floor(marked*0.75)>= 1+std::floor(len1*0.4)){
            std::cout<<"changed"<<std::endl;
            return CHANGED;
        }
    }
    return decision;
}

void Lcs::clearRelation(relation &rel){
    if(rel.children.size()){
        for(int i=0; i<rel.children.size();++i){
            clearRelation(rel.children[i]);
        }
        rel.children.clear();
    }
    rel.releativesIndex=NO_RELATIVES;
    rel.typeOfReleation=UNMATCHED;
    return;
}

int Lcs::checkListsRelations(const QStringList &list1, const QStringList &list2,
                             std::vector<relation> &rel1, std::vector<relation> &rel2,
                             relation *parent1, relation *parent2){
    int len1 = getNumberOfLines(list1);
    int len2 = getNumberOfLines(list2);

    rel1.resize(len1);
    rel2.resize(len2);

    std::for_each(rel1.begin(), rel1.end(), [&](relation &r){r.parent=parent1;});
    std::for_each(rel2.begin(), rel2.end(), [&](relation &r){r.parent=parent2;});

    //get first level lcs matrix and mark all matches as moved
    int** lcsMatrix = getLcsMatrix(list1, list2);

    //mark matches by backracking
    backtrackAndMark(lcsMatrix, rel1, rel2, list1, list2);

    return lcsMatrix[len1-1][len2-1];
}


QStringList Lcs::separate(const QString &text, int level){
    QStringList list = text.split(SEPARATORS[level][0]);
    for(QStringList::const_iterator iter = ++SEPARATORS[level].cbegin();
        iter<SEPARATORS[level].cend(); ++iter){
        for(int idx = 0; idx<list.count(); ++idx){
            QStringList tmp_list = list[idx].split(*iter);
            if(tmp_list.count()>1){
                list[idx] = tmp_list[0];
                for(int tmp_idx = 1; tmp_idx < tmp_list.count();++tmp_idx, ++idx){
                    list.insert(idx+tmp_idx-1, tmp_list[tmp_idx]); //-1 because we want to
                }                                    //to point the place to insert behind
            }
        }
    }
    return list;
}


int Lcs::getNumberOfLines(const QString &text){
    return text.count("\n");
}

int Lcs::getNumberOfLines(const QStringList &textList){
    return textList.count();
}

int Lcs::getContainedSize(const QString &container,
                          QStringList::const_iterator iter,
                          QStringList::const_iterator end){
    int containedCount = 0;
    QString text = *iter;
    while(container.contains(text) && ++iter!=end){
        ++containedCount;
        text.append(" " + *iter);
    }
    return containedCount;
}
