#include <QtTest>
#include <QString>

#include <iostream>

#include "../lcs.h"


class LcsInitTest : public QObject
{
    Q_OBJECT

public:
    LcsInitTest();
    ~LcsInitTest();

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
};

LcsInitTest::LcsInitTest(){}

LcsInitTest::~LcsInitTest(){}




// uniniciated

void LcsInitTest::test_uniniciated_left_relation(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(0),
                             Lcs::UniniciatedException);
}
void LcsInitTest::test_uniniciated_right_relation(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(0),
                             Lcs::UniniciatedException);
}

void LcsInitTest::test_uniniciated_left_relation_idx(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(0),
                             Lcs::UniniciatedException);
}
void LcsInitTest::test_uniniciated_right_relation_idx(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(0),
                             Lcs::UniniciatedException);
}

void LcsInitTest::test_uniniciated_increment(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromLeft(0),
                             Lcs::UniniciatedException);
    QVERIFY_EXCEPTION_THROWN(l.incrementLevelFromRight(0),
                             Lcs::UniniciatedException);
}
void LcsInitTest::test_uniniciated_decremetn(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.decrementLevel(),
                             Lcs::UniniciatedException);
}
void LcsInitTest::test_uniniciated_change_relation(){
    Lcs l;
    QVERIFY_EXCEPTION_THROWN(l.changeRelation(Lcs::MATCHED, 0, 0),
                             Lcs::UniniciatedException);
}




//empty left

void LcsInitTest::test_init_empty_left_left_relation(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(2), std::out_of_range);
}

void LcsInitTest::test_init_empty_left_right_relation(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY(l.getRelationTypeRight(0) == Lcs::UNMATCHED);
    QVERIFY(l.getRelationTypeRight(1) == Lcs::UNMATCHED);
}

void LcsInitTest::test_init_empty_left_left_relation_idx(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(2), std::out_of_range);
}
void LcsInitTest::test_init_empty_left_right_relation_idx(){
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY(l.getRelationIndexRight(0) == Lcs::NO_RELATIVES);
    QVERIFY(l.getRelationIndexRight(1) == Lcs::NO_RELATIVES);
}

void LcsInitTest::test_init_empty_left_increment(){
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

void LcsInitTest::test_init_empty_left_change_relation()
{
    QString textLeft;
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    // cannot change relations because the other side is empty
    QVERIFY_EXCEPTION_THROWN(l.changeRelation(Lcs::MATCHED, 0, 0), std::out_of_range);
}





// empty right

void LcsInitTest::test_init_empty_right_left_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY(l.getRelationTypeLeft(0) == Lcs::UNMATCHED);
    QVERIFY(l.getRelationTypeLeft(1) == Lcs::UNMATCHED);
}

void LcsInitTest::test_init_empty_right_right_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(2), std::out_of_range);
}

void LcsInitTest::test_init_empty_right_left_relation_idx(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY(l.getRelationIndexLeft(0) == Lcs::NO_RELATIVES);
    QVERIFY(l.getRelationIndexLeft(1) == Lcs::NO_RELATIVES);
}
void LcsInitTest::test_init_empty_right_right_relation_idx(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(2), std::out_of_range);
}

void LcsInitTest::test_init_empty_right_increment(){
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

void LcsInitTest::test_init_empty_right_change_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // cannot change relations because the other side is empty
    QVERIFY_EXCEPTION_THROWN(l.changeRelation(Lcs::MATCHED, 0, 0), std::out_of_range);
}





// both empty

void LcsInitTest::test_init_empty_both_left_relation(){
    QString textLeft;
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeLeft(2), std::out_of_range);
}

void LcsInitTest::test_init_empty_both_right_relation(){
    QString textLeft;
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationTypeRight(2), std::out_of_range);
}

void LcsInitTest::test_init_empty_both_left_relation_idx(){
    QString textLeft;
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // right sides lines are unmatched
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexLeft(2), std::out_of_range);
}

void LcsInitTest::test_init_empty_both_right_relation_idx(){
    QString textLeft;
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // the vector for ralations that are not there is empty
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(0), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(l.getRelationIndexRight(2), std::out_of_range);
}

void LcsInitTest::test_init_empty_both_increment(){
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

void LcsInitTest::test_init_empty_both_change_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight;

    Lcs l;
    l.initiate(textLeft, textRight);

    // cannot change relations because the other side is empty
    QVERIFY_EXCEPTION_THROWN(l.changeRelation(Lcs::MATCHED, 0, 0), std::out_of_range);
}




// both full

void LcsInitTest::test_init_full_both_left_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeLeft(0)==Lcs::MATCHED);
}

void LcsInitTest::test_init_full_both_right_relation_idx(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexRight(0)!=Lcs::NO_RELATIVES);
}

void LcsInitTest::test_init_full_both_left_relation_idx(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationIndexLeft(0)!=Lcs::NO_RELATIVES);
}

void LcsInitTest::test_init_full_both_right_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.getRelationTypeRight(0)==Lcs::MATCHED);
}

void LcsInitTest::test_init_full_both_increment_left(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.incrementLevelFromLeft(0));
}

void LcsInitTest::test_init_full_both_increment_right(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.incrementLevelFromRight(0));
}

void LcsInitTest::test_init_full_both_decrement(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    l.incrementLevelFromRight(0);
    QVERIFY(l.decrementLevel());
}

void LcsInitTest::test_init_full_both_change_relation(){
    QString textLeft = "First line.\nSecond line.";
    QString textRight = "First line.\nSecond line.";

    Lcs l;
    l.initiate(textLeft, textRight);

    QVERIFY(l.changeRelation(Lcs::MATCHED, 0, 0));
}


QTEST_APPLESS_MAIN(LcsInitTest)

#include "tst_lcs_init_test.moc"
