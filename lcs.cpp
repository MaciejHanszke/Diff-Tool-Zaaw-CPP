#include "lcs.h"


#include <algorithm>
#include <array>
#include <cstddef>
#include <cmath>

#include <QFile>
#include <QTextStream>
#include <iostream>


namespace  {
    static const QStringList PARAGRAPH_SEPARATORS = {"\n"};
    static const QStringList SENTENCE_SEPARATORS = {". ", "? ","! "};
    static const QStringList WORD_SEPARATORS = {" "};
    static const std::array<QStringList, 3> SEPARATORS = {PARAGRAPH_SEPARATORS,
                                                 SENTENCE_SEPARATORS,
                                                 WORD_SEPARATORS};
}


Lcs::Lcs()
{
    currentLevel=0;
    currentLeftParent = nullptr;
    currentRightParent = nullptr;
    state = Lcs::State::UNINICIATED;
}

//   #####################################
//   ################ api ################
//   #####################################

bool Lcs::initiate(const QString &text1, const QString &text2){
    try{
        initRelations(text1, levelZeroRelations1, 0, nullptr);
        initRelations(text2, levelZeroRelations2, 0, nullptr);
        checkRelations(text1, text2, 0, levelZeroRelations1, levelZeroRelations2);
        state = Lcs::State::INICIATED;
        return true;
    } catch (const std::exception&){
        return false;
    }
}

int Lcs::getRelationTypeLeft(int idxLeft){
    if(state == Lcs::State::UNINICIATED){
        throw UniniciatedException();
    }
    if(!currentLevel){
        if(levelZeroRelations1.empty())
            throw std::out_of_range("levelZeroRelations1");
        return levelZeroRelations1.at(idxLeft).typeOfReleation;
    } else {
        if(currentLeftParent->children.empty())
            throw std::out_of_range("currentLeftParent->children");
        return currentLeftParent->children.at(idxLeft).typeOfReleation;
    }
    return -1;
}

int Lcs::getRelationTypeRight(int idxRight){
    if(state == Lcs::State::UNINICIATED){
        throw UniniciatedException();
    }
    if(!currentLevel){
        if(levelZeroRelations2.empty())
            throw std::out_of_range("levelZeroRelations2");
        return levelZeroRelations2.at(idxRight).typeOfReleation;
    } else {
        if(currentRightParent->children.empty())
            throw std::out_of_range("currentRightParent->children");
        return currentRightParent->children.at(idxRight).typeOfReleation;
    }
    return -1;
}

int Lcs::getRelationIndexLeft(int idxLeft){
    if(state == Lcs::State::UNINICIATED){
        throw UniniciatedException();
    }
    if(!currentLevel){
        if(levelZeroRelations1.empty())
            throw std::out_of_range("levelZeroRelations1");
        return levelZeroRelations1.at(idxLeft).releativesIndex;
    } else {
        if(currentLeftParent->children.empty())
            throw std::out_of_range("currentLeftParent->children");
        return currentLeftParent->children.at(idxLeft).releativesIndex;
    }
    return -1;
}

int Lcs::getRelationIndexRight(int idxRight){
    if(state == Lcs::State::UNINICIATED){
        throw UniniciatedException();
    }
    if(!currentLevel){
        if(levelZeroRelations2.empty())
            throw std::out_of_range("levelZeroRelations2");
        return levelZeroRelations2.at(idxRight).releativesIndex;
    } else {
        if(currentRightParent->children.empty())
            throw std::out_of_range("currentRightParent->children");
        return currentRightParent->children.at(idxRight).releativesIndex;
    }
    return -1;
}

bool Lcs::incrementLevelFromLeft(int idxLeft){
    if(state == Lcs::State::UNINICIATED){
        throw UniniciatedException();
    }
    if(currentLevel==SEPARATORS.size()-1){
        throw IncrementMaxLevelException();
    }
    if(levelZeroRelations1.empty() || levelZeroRelations2.empty()){
        throw IncrementingEmptySideException();
    }
    if(!currentLevel){
        currentLeftParent = &levelZeroRelations1[idxLeft];
        if(currentLeftParent->releativesIndex!=NO_RELATIVES){
            currentRightParent = &levelZeroRelations2[currentLeftParent->releativesIndex];
        } else {
            currentRightParent = nullptr;
        }
    } else {
        currentLeftParent = &currentLeftParent->children.at(idxLeft);
        if(currentLeftParent->releativesIndex!=NO_RELATIVES){
            currentRightParent = &currentRightParent->children[currentLeftParent->releativesIndex];
        } else {
            currentRightParent = nullptr;
        }
    }
    ++currentLevel;
    return true;
}

bool Lcs::incrementLevelFromRight(int idxRight){
    if(state == Lcs::State::UNINICIATED){
        throw UniniciatedException();
    } else if(currentLevel==SEPARATORS.size()-1){
        throw IncrementMaxLevelException();
    } else if(levelZeroRelations1.empty() || levelZeroRelations2.empty()){
        throw IncrementingEmptySideException();
    }
    if(!currentLevel){
        currentRightParent = &levelZeroRelations2.at(idxRight);
        if(currentRightParent->releativesIndex!=NO_RELATIVES){
            currentLeftParent = &levelZeroRelations1[currentRightParent->releativesIndex];
        } else {
            currentLeftParent = nullptr;
        }
    } else {
        currentRightParent = &currentRightParent->children.at(idxRight);
        if(currentRightParent->releativesIndex!=NO_RELATIVES){
            currentLeftParent = &currentLeftParent->children[currentRightParent->releativesIndex];
        } else {
            currentLeftParent = nullptr;
        }
    }
    ++currentLevel;
    return true;
}

bool Lcs::decrementLevel(){
    if(state == Lcs::State::UNINICIATED){
        throw UniniciatedException();
    } else if(!currentLevel){
        throw DecrementZeroLevelException();
    }
    currentLeftParent = currentLeftParent->parent;
    currentRightParent = currentRightParent->parent;
    --currentLevel;
    return true;
}

bool Lcs::changeRelation(int relationType, int idxLeft, int idxRight){
    if(state == Lcs::State::UNINICIATED){
        throw UniniciatedException();
    } else if(currentLevel==SEPARATORS.size()){
        throw ChangingMaxLevelException();
    }
    if(currentLevel == 0 ){
        if(levelZeroRelations1.empty() || levelZeroRelations2.empty()){
            throw std::out_of_range("trying to change empty vector");
        } if (levelZeroRelations1.at(idxLeft).releativesIndex!=Lcs::NO_RELATIVES){
            levelZeroRelations2.at(levelZeroRelations1.at(idxLeft).releativesIndex).releativesIndex=Lcs::NO_RELATIVES;
            levelZeroRelations2.at(levelZeroRelations1.at(idxLeft).releativesIndex).typeOfReleation=Lcs::UNMATCHED;
        } if (levelZeroRelations2.at(idxRight).releativesIndex!=Lcs::NO_RELATIVES){
            levelZeroRelations1.at(levelZeroRelations2.at(idxRight).releativesIndex).releativesIndex=Lcs::NO_RELATIVES;
            levelZeroRelations1.at(levelZeroRelations2.at(idxRight).releativesIndex).typeOfReleation=Lcs::UNMATCHED;
        }
        levelZeroRelations1.at(idxLeft).releativesIndex=idxRight;
        levelZeroRelations2.at(idxRight).releativesIndex=idxLeft;
        levelZeroRelations1.at(idxLeft).typeOfReleation=relationType;
        levelZeroRelations2.at(idxRight).typeOfReleation=relationType;
    } else {
        if(currentLeftParent->children.empty() ||
                currentRightParent->children.empty()){
            throw std::out_of_range("trying to change empty vector");
        } if(currentLeftParent->children.at(idxLeft).releativesIndex!=Lcs::NO_RELATIVES){
            currentRightParent->children.at(currentLeftParent->children.at(idxLeft).releativesIndex).releativesIndex=Lcs::NO_RELATIVES;
            currentRightParent->children.at(currentLeftParent->children.at(idxLeft).releativesIndex).typeOfReleation=Lcs::UNMATCHED;
        } if(currentRightParent->children.at(idxRight).releativesIndex!=Lcs::NO_RELATIVES){
            currentLeftParent->children.at(currentRightParent->children.at(idxRight).releativesIndex).releativesIndex=Lcs::NO_RELATIVES;
            currentLeftParent->children.at(currentRightParent->children.at(idxRight).releativesIndex).typeOfReleation=Lcs::UNMATCHED;
        }
        currentLeftParent->children.at(idxLeft).releativesIndex=idxRight;
        currentRightParent->children.at(idxRight).releativesIndex=idxLeft;
        currentLeftParent->children.at(idxLeft).typeOfReleation=relationType;
        currentRightParent->children.at(idxRight).typeOfReleation=relationType;
    }
    return true;
}

//   #####################################
//   ############## end api ##############
//   #####################################


void Lcs::initRelations(const QString &text, std::vector<relation> &rel,
                        uint level, relation *parent){
    if(text.isEmpty()){
        return;
    }

    QStringList list = separate(text, level);

    int len = getNumberOfLines(list);
    rel.resize(len);

    std::for_each(rel.begin(), rel.end(), [&](relation &r){r.parent=parent;});

    if(level < SEPARATORS.size()-1 && len != 0){
        for(int i=0; i<len; ++i){
            initRelations(list[i], rel[i].children, level+1, &rel[i]);
        }
    }
    return;
}

int** Lcs::getLcsMatrix(const QStringList &list1, const QStringList &list2){
    int len1 = getNumberOfLines(list1);
    int len2 = getNumberOfLines(list2);

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
    return lcsMatrix;
}

void Lcs::backtrackAndMark(int** lcsMatrix, std::vector<relation> &rel1, std::vector<relation> &rel2,
                           const QStringList &list1, const QStringList &list2){
    int len1 = rel1.size();
    int len2 = rel2.size();
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
    int len1 = rel1.size();
    int len2 = rel2.size();
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

int Lcs::checkRelations(const QString &text1, const QString &text2, uint level,
                        std::vector<relation> &rel1, std::vector<relation> &rel2){
    int decision = UNMATCHED;

    //split texts into lists
    QStringList list1 = separate(text1, level);
    QStringList list2 = separate(text2, level);

    int len1 = rel1.size();
    int len2 = rel2.size();


    int matched = checkListsRelations(list1, list2, rel1, rel2);
    int moved = markMoved(rel1, rel2, list1, list2);

    if(level==SEPARATORS.size()-1){
        if(matched+moved >= 1+std::floor(len1*0.6)){
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
                                                 rel1[i].children, rel2[j].children);
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
        if(matched+moved+marked>= 1+std::floor(len1*0.6)){
            return CHANGED;
        }
    }
    return decision;
}

void Lcs::clearRelation(relation &rel){
    if(rel.children.size() != 0){
        std::for_each(rel.children.begin(), rel.children.end(),
                      [&](relation &r){clearRelation(r);});
    }
    rel.releativesIndex=NO_RELATIVES;
    rel.typeOfReleation=UNMATCHED;
    return;
}

int Lcs::checkListsRelations(const QStringList &list1, const QStringList &list2,
                             std::vector<relation> &rel1, std::vector<relation> &rel2){
    int len1 = getNumberOfLines(list1);
    int len2 = getNumberOfLines(list2);

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


//   #####################################
//   ############# exception #############
//   #####################################

const char * Lcs::UniniciatedException::what () const throw ()
{
    return "Lcs was not iniciated";
}

const char * Lcs::DecrementZeroLevelException::what () const throw ()
{
    return "Trying to decrement form the lowest level";
}

const char * Lcs::IncrementMaxLevelException::what () const throw ()
{
    return "Trying to increment maximum level";
}

const char * Lcs::ChangingMaxLevelException::what () const throw ()
{
    return "Cannot apply changes to relations at max level, decrement level to do so";
}

const char * Lcs::IncrementingEmptySideException::what () const throw ()
{
    return "Cannot increment epmty text.";
}

//   #####################################
//   ########### end exception ###########
//   #####################################
