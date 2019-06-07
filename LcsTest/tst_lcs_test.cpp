#include <QtTest>
#include <QString>

#include <iostream>

#include "../lcs.h"


class LcsTest : public QObject
{
    Q_OBJECT

public:
    LcsTest();
    ~LcsTest();

private slots:
    void test_uniniciated_left_relation();
    void test_uniniciated_right_relation();
    void test_uniniciated_left_relation_idx();
    void test_uniniciated_right_relation_idx();
    void test_uniniciated_increment();
    void test_uniniciated_decremetn();
    void test_uniniciated_change_relation();

    void test_init_empty_left_left_relation();
    void test_init_empty_left_right_relation();
    void test_init_empty_left_left_relation_idx();
    void test_init_empty_left_right_relation_idx();
    void test_init_empty_left_increment();
    void test_init_empty_left_change_relation();

    void test_init_empty_right_left_relation();
    void test_init_empty_right_right_relation();
    void test_init_empty_right_left_relation_idx();
    void test_init_empty_right_right_relation_idx();
    void test_init_empty_right_increment();
    void test_init_empty_right_change_relation();

    void test_init_empty_both_left_relation();
    void test_init_empty_both_right_relation();
    void test_init_empty_both_right_relation_idx();
    void test_init_empty_both_left_relation_idx();
    void test_init_empty_both_increment();
    void test_init_empty_both_change_relation();

    void test_init_full_both_left_relation();
    void test_init_full_both_right_relation();
    void test_init_full_both_left_relation_idx();
    void test_init_full_both_right_relation_idx();
    void test_init_full_both_increment_left();
    void test_init_full_both_increment_right();
    void test_init_full_both_decrement();
    void test_init_full_both_change_relation();

    void test_get_ralation_left_match();
    void test_get_ralation_left_unmatched();
    void test_get_ralation_left_moved();
    void test_get_ralation_left_changed();

    void test_get_index_left_match();
    void test_get_index_left_unmatched();
    void test_get_index_left_moved();
    void test_get_index_left_changed();

    void test_get_ralation_right_match();
    void test_get_ralation_right_unmatched();
    void test_get_ralation_right_moved();
    void test_get_ralation_right_changed();

    void test_get_index_right_match();
    void test_get_index_right_unmatched();
    void test_get_index_right_moved();
    void test_get_index_right_changed();

    void test_change_relation();
    void test_change_relation_move();

    void test_increment_left();
    void test_increment_right();
    void test_increment_change();
    void test_increment_max();

    void test_decrement();
    void test_decrement_change();
    void test_decrement_max();

};

LcsTest::LcsTest(){}

LcsTest::~LcsTest(){}




// uniniciated

void LcsTest::test_uniniciated_left_relation(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(0),
                             Lcs::UniniciatedException);
}
void LcsTest::test_uniniciated_right_relation(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(0),
                             Lcs::UniniciatedException);
}

void LcsTest::test_uniniciated_left_relation_idx(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(0),
                             Lcs::UniniciatedException);
}
void LcsTest::test_uniniciated_right_relation_idx(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(0),
                             Lcs::UniniciatedException);
}

void LcsTest::test_uniniciated_increment(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromLeft(0),
                             Lcs::UniniciatedException);
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromRight(0),
                             Lcs::UniniciatedException);
}
void LcsTest::test_uniniciated_decremetn(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.decrementLevel(),
                             Lcs::UniniciatedException);
}
void LcsTest::test_uniniciated_change_relation(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.changeRelation(Lcs::MATCHED, 0, 0),
                             Lcs::UniniciatedException);
}




//empty left

void LcsTest::test_init_empty_left_left_relation(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(2), std::out_of_range);
}

void LcsTest::test_init_empty_left_right_relation(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY(l.getRelationTypeRight(0) == Lcs::UNMATCHED);
    QVERIFY(l.getRelationTypeRight(1) == Lcs::UNMATCHED);
}

void LcsTest::test_init_empty_left_left_relation_idx(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(2), std::out_of_range);
}
void LcsTest::test_init_empty_left_right_relation_idx(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY(l.getRelationIndexRight(0) == Lcs::NO_RELATIVES);
    QVERIFY(l.getRelationIndexRight(1) == Lcs::NO_RELATIVES);
}

void LcsTest::test_init_empty_left_increment(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // block increment
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromLeft(0),
                             Lcs::IncrementingEmptySideException);
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromRight(0),
                             Lcs::IncrementingEmptySideException);
}

void LcsTest::test_init_empty_left_change_relation()
{
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // cannot change relations because the other side is empty
    QVERIFY_EXCEPTION_THROWN(l.changeRelation(Lcs::MATCHED, 0, 0), std::out_of_range);
}





// empty right

void LcsTest::test_init_empty_right_left_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY(l.getRelationTypeLeft(0) == Lcs::UNMATCHED);
    QVERIFY(l.getRelationTypeLeft(1) == Lcs::UNMATCHED);
}

void LcsTest::test_init_empty_right_right_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(2), std::out_of_range);
}

void LcsTest::test_init_empty_right_left_relation_idx(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY(l.getRelationIndexLeft(0) == Lcs::NO_RELATIVES);
    QVERIFY(l.getRelationIndexLeft(1) == Lcs::NO_RELATIVES);
}
void LcsTest::test_init_empty_right_right_relation_idx(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(2), std::out_of_range);
}

void LcsTest::test_init_empty_right_increment(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // cannot increment
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromRight(0),
                             Lcs::IncrementingEmptySideException);
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromLeft(0),
                             Lcs::IncrementingEmptySideException);
}

void LcsTest::test_init_empty_right_change_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // cannot change relations because the other side is empty
    QVERIFY_EXCEPTION_THROWN(l.changeRelation(Lcs::MATCHED, 0, 0), std::out_of_range);
}





// both empty

void LcsTest::test_init_empty_both_left_relation(){
    QString textLeft;
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(2), std::out_of_range);
}

void LcsTest::test_init_empty_both_right_relation(){
    QString textLeft;
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(2), std::out_of_range);
}

void LcsTest::test_init_empty_both_left_relation_idx(){
    QString textLeft;
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(2), std::out_of_range);
}

void LcsTest::test_init_empty_both_right_relation_idx(){
    QString textLeft;
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(2), std::out_of_range);
}

void LcsTest::test_init_empty_both_increment(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // cannot increment
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromRight(0),
                             Lcs::IncrementingEmptySideException);
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromLeft(0),
                             Lcs::IncrementingEmptySideException);
}

void LcsTest::test_init_empty_both_change_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // cannot change relations because the other side is empty
    QVERIFY_EXCEPTION_THROWN(l.changeRelation(Lcs::MATCHED, 0, 0), std::out_of_range);
}




// both full

void LcsTest::test_init_full_both_left_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeLeft(0)==Lcs::MATCHED);
}

void LcsTest::test_init_full_both_right_relation_idx(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexRight(0)!=Lcs::NO_RELATIVES);
}

void LcsTest::test_init_full_both_left_relation_idx(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexLeft(0)!=Lcs::NO_RELATIVES);
}

void LcsTest::test_init_full_both_right_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeRight(0)==Lcs::MATCHED);
}

void LcsTest::test_init_full_both_increment_left(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.incrementLevelFromLeft(0));
}

void LcsTest::test_init_full_both_increment_right(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.incrementLevelFromRight(0));
}

void LcsTest::test_init_full_both_decrement(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    l.incrementLevelFromRight(0);
    QVERIFY(l.decrementLevel());
}

void LcsTest::test_init_full_both_change_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.changeRelation(Lcs::MATCHED, 0, 0));
}

void LcsTest::test_get_ralation_left_match(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeLeft(0)==Lcs::MATCHED);
    QVERIFY(l.getRelationTypeLeft(1)==Lcs::MATCHED);
}

void LcsTest::test_get_ralation_left_unmatched(){
    QString textLeft  = "First line.\nSecond line.";
    QString textRight = "No match line one.\nNo match line two.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeLeft(0)==Lcs::UNMATCHED);
    QVERIFY(l.getRelationTypeLeft(1)==Lcs::UNMATCHED);
}

void LcsTest::test_get_ralation_left_moved(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "Second line.\nFirst line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeLeft(0)==Lcs::MATCHED);
    QVERIFY(l.getRelationTypeLeft(1)==Lcs::MOVED);
}

void LcsTest::test_get_ralation_left_changed(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "Second change line.\nFirst change line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeLeft(0)==Lcs::CHANGED);
    QVERIFY(l.getRelationTypeLeft(1)==Lcs::CHANGED);
}

void LcsTest::test_get_index_left_match(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexLeft(0)==0);
    QVERIFY(l.getRelationIndexLeft(1)==1);
}

void LcsTest::test_get_index_left_unmatched(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "No match line one.\nNo match line two.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexLeft(0)==Lcs::NO_RELATIVES);
    QVERIFY(l.getRelationIndexLeft(1)==Lcs::NO_RELATIVES);
}

void LcsTest::test_get_index_left_moved(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "Second line.\nFirst line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexLeft(0)==1);
    QVERIFY(l.getRelationIndexLeft(1)==0);
}

void LcsTest::test_get_index_left_changed(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "Second change line.\nFirst change line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexLeft(0)==1);
    QVERIFY(l.getRelationIndexLeft(1)==0);
}

void LcsTest::test_get_ralation_right_match(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeRight(0)==Lcs::MATCHED);
    QVERIFY(l.getRelationTypeRight(1)==Lcs::MATCHED);
}

void LcsTest::test_get_ralation_right_unmatched(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "No match line one.\nNo match line two.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeRight(0)==Lcs::UNMATCHED);
    QVERIFY(l.getRelationTypeRight(1)==Lcs::UNMATCHED);
}

void LcsTest::test_get_ralation_right_moved(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "Second line.\nFirst line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeRight(0)==Lcs::MOVED);
    QVERIFY(l.getRelationTypeRight(1)==Lcs::MATCHED);
}

void LcsTest::test_get_ralation_right_changed(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "Second change line.\nFirst change line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeRight(0)==Lcs::CHANGED);
    QVERIFY(l.getRelationTypeRight(1)==Lcs::CHANGED);
}

void LcsTest::test_get_index_right_match(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexRight(0)==0);
    QVERIFY(l.getRelationIndexRight(1)==1);
}

void LcsTest::test_get_index_right_unmatched(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "No match line one.\nNo match line two.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexRight(0)==Lcs::NO_RELATIVES);
    QVERIFY(l.getRelationIndexRight(1)==Lcs::NO_RELATIVES);
}

void LcsTest::test_get_index_right_moved(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "Second line.\nFirst line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexRight(0)==1);
    QVERIFY(l.getRelationIndexRight(1)==0);
}

void LcsTest::test_get_index_right_changed(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "Second change line.\nFirst change line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexRight(0)==1);
    QVERIFY(l.getRelationIndexRight(1)==0);
}

void LcsTest::test_change_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    l.changeRelation(Lcs::CHANGED, 0,0);

    QVERIFY(l.getRelationTypeLeft(0)==Lcs::CHANGED);
    QVERIFY(l.getRelationTypeRight(0)==Lcs::CHANGED);

    QVERIFY(l.getRelationIndexLeft(0)==0);
    QVERIFY(l.getRelationIndexRight(0)==0);
}

void LcsTest::test_change_relation_move(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    l.changeRelation(Lcs::MATCHED, 0,1);

    QVERIFY(l.getRelationTypeLeft(0)==Lcs::MATCHED);
    QVERIFY(l.getRelationTypeRight(0)==Lcs::UNMATCHED);
    QVERIFY(l.getRelationTypeLeft(1)==Lcs::UNMATCHED);
    QVERIFY(l.getRelationTypeRight(1)==Lcs::MATCHED);

    QVERIFY(l.getRelationIndexLeft(0)==1);
    QVERIFY(l.getRelationIndexRight(1)==0);
    QVERIFY(l.getRelationIndexLeft(1)==Lcs::NO_RELATIVES);
    QVERIFY(l.getRelationIndexRight(0)==Lcs::NO_RELATIVES);
}

void LcsTest::test_increment_left(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First change line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);
    l.incrementLevelFromLeft(0);
    l.incrementLevelFromLeft(0);

    QVERIFY(l.getRelationTypeLeft(1)==Lcs::MATCHED);
    QVERIFY(l.getRelationIndexLeft(1)==2);

    QVERIFY(l.getRelationTypeRight(1)==Lcs::UNMATCHED);
    QVERIFY(l.getRelationIndexRight(1)==Lcs::NO_RELATIVES);
}

void LcsTest::test_increment_right(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First change line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);
    l.incrementLevelFromRight(0);
    l.incrementLevelFromRight(0);

    QVERIFY(l.getRelationTypeLeft(1)==Lcs::MATCHED);
    QVERIFY(l.getRelationIndexLeft(1)==2);

    QVERIFY(l.getRelationTypeRight(1)==Lcs::UNMATCHED);
    QVERIFY(l.getRelationIndexRight(1)==Lcs::NO_RELATIVES);
}

void LcsTest::test_increment_change(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First change line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);
    l.incrementLevelFromRight(0);
    l.incrementLevelFromRight(0);
    l.changeRelation(Lcs::MATCHED, 1, 1);

    QVERIFY(l.getRelationTypeLeft(1)==Lcs::MATCHED);
    QVERIFY(l.getRelationIndexLeft(1)==1);

    QVERIFY(l.getRelationTypeRight(1)==Lcs::MATCHED);
    QVERIFY(l.getRelationIndexRight(1)==1);

    QVERIFY(l.getRelationTypeRight(2)==Lcs::UNMATCHED);
    QVERIFY(l.getRelationIndexLeft(1)==Lcs::NO_RELATIVES);
}

void LcsTest::test_increment_max(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First change line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);
    l.incrementLevelFromRight(0);
    l.incrementLevelFromRight(0);
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromRight(0),
                             Lcs::IncrementMaxLevelException);
}

void LcsTest::test_decrement(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First change line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);
    l.incrementLevelFromRight(0);
    l.decrementLevel();

    QVERIFY(l.getRelationTypeLeft(1)==Lcs::MATCHED);
    QVERIFY(l.getRelationIndexLeft(1)==1);

    QVERIFY(l.getRelationTypeRight(1)==Lcs::MATCHED);
    QVERIFY(l.getRelationIndexRight(1)==1);
}

void LcsTest::test_decrement_change(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First change line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);
    l.incrementLevelFromRight(0);
    l.decrementLevel();
    l.changeRelation(Lcs::CHANGED, 1, 1);

    QVERIFY(l.getRelationTypeLeft(1)==Lcs::CHANGED);
    QVERIFY(l.getRelationIndexLeft(1)==1);

    QVERIFY(l.getRelationTypeRight(1)==Lcs::CHANGED);
    QVERIFY(l.getRelationIndexRight(1)==1);
}
void LcsTest::test_decrement_max(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First change line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);
    QVERIFY_EXCEPTION_THROWN(l.decrementLevel(),
                             Lcs::DecrementZeroLevelException);
}

QTEST_APPLESS_MAIN(LcsTest)

#include "tst_lcs_test.moc"
