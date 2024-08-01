#include "header.h"
#include "header1.h"

#include <gtest/gtest.h>

TEST(Student, Init) {
    Student st("Artyom", "IU8-35", {5, 5, 5});
    EXPECT_EQ(st.getName(), "Artyom");
    EXPECT_EQ(st.getGroup(), "IU8-35");
}

TEST(Student, getMarks) {
    Student st("Artyom", "IU8-35", {5, 2, 5});
    EXPECT_EQ(st.sumMarks(2), 2);
}

TEST(Student, checkFive) {
    Student st("Artyom", "IU8-35", {5, 5, 5});
    EXPECT_TRUE(st.checkFive());
}

TEST(Student, checkDebt) {
    Student st("Artyom", "IU8-35", {2, 5, 5});
    EXPECT_TRUE(st.checkDebt());
}

TEST(Group, Init) {
    Student st("Artyom", "IU8-35", {5, 5, 5});
    Student st1("Sasha", "IU8-35", {5, 5, 5});
    Group gr("IU8-35", {st, st1});
    EXPECT_EQ(gr.getGroup(), "IU8-35");
    for (auto el: gr.getStudents()) {
        EXPECT_EQ(el.getGroup(), "IU8-35");
    }
}

TEST(Group, middleMarks) {
    Student st("Artyom", "IU8-35", {5, 5, 5});
    Student st1("Sasha", "IU8-35", {4, 4, 4});
    Group gr("IU8-35", {st, st1});
    EXPECT_EQ(4.5, gr.middleMarks(2));
}


TEST(Group, changeGroup) {
    Student st("Artyom", "IU8-35", {5, 5, 5});
    Student st1("Sasha", "IU8-35", {4, 4, 4});
    Student st3("Artyom", "IU8-35", {4, 5, 5});
    Group gr("IU8-35", {st, st1});
    gr.changeGroup(st3);
    EXPECT_EQ(gr.getStudents().size(), 2);
    for (auto el: gr.getStudents()) {
        EXPECT_EQ(el.sumMarks(1), 4);
        break;
    }
}
