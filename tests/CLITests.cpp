#include <gtest/gtest.h>

#include "../src/cli/ArgumentParser.hpp"



//HELP


TEST(ParserTest, HelpWhenNoArguments) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo"};

    auto result = parser.parse(1,argv);

    EXPECT_TRUE(std::holds_alternative<HelpArguments>(result));
}

TEST(ParserTest, ExplicitHelpCommand) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo",(char*)"help"};

    auto result = parser.parse(2,argv);

    EXPECT_TRUE(std::holds_alternative<HelpArguments>(result));
}




   //STATS

TEST(ParserTest, StatsCommand) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo",(char*)"stats"};

    auto result = parser.parse(2,argv);

    EXPECT_TRUE(std::holds_alternative<StatsArguments>(result));
}




   //LIST


TEST(ParserTest, ListCommand) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo",(char*)"list"};

    auto result = parser.parse(2,argv);

    EXPECT_TRUE(std::holds_alternative<ListArguments>(result));
}

TEST(ParserTest, ListDoneFlag) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo",(char*)"list",(char*)"--done"};

    auto result = parser.parse(3,argv);

    auto args = std::get<ListArguments>(result);

    EXPECT_TRUE(args.ifDone);
}

TEST(ParserTest, ListPriorityFilter) {

    ArgumentParser parser;

    char* argv[] = {
        (char*)"todo",
        (char*)"list",
        (char*)"--priority",
        (char*)"high"
    };

    auto result = parser.parse(4,argv);

    auto args = std::get<ListArguments>(result);

    ASSERT_TRUE(args.priorityFilter.has_value());
    EXPECT_EQ(args.priorityFilter.value(),"high");
}




   //DONE


TEST(ParserTest, DoneCommand) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo",(char*)"done",(char*)"3"};

    auto result = parser.parse(3,argv);

    auto args = std::get<DoneArguments>(result);

    EXPECT_EQ(args.id,3);
}




   //SEARCH


TEST(ParserTest, SearchCommand) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo",(char*)"search",(char*)"milk"};

    auto result = parser.parse(3,argv);

    auto args = std::get<SearchArguments>(result);

    EXPECT_EQ(args.word,"milk");
}




   //ADD SIMPLE TASK


TEST(ParserTest, AddSimpleTask) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo",(char*)"add",(char*)"Task"};

    auto result = parser.parse(3,argv);

    auto args = std::get<AddArguments>(result);

    EXPECT_EQ(args.title,"Task");
    EXPECT_FALSE(args.priority.has_value());
}




   //ADD WITH PRIORITY


TEST(ParserTest, AddWithPriority) {

    ArgumentParser parser;

    char* argv[] = {
        (char*)"todo",
        (char*)"add",
        (char*)"Task",
        (char*)"--priority",
        (char*)"high"
    };

    auto result = parser.parse(5,argv);

    auto args = std::get<AddArguments>(result);

    ASSERT_TRUE(args.priority.has_value());
    EXPECT_EQ(args.priority.value(),"high");
}




   //ADD DEADLINE TASK


TEST(ParserTest, AddDeadlineTask) {

    ArgumentParser parser;

    char* argv[] = {
        (char*)"todo",
        (char*)"add",
        (char*)"Task",
        (char*)"--deadline",
        (char*)"2025-06-01"
    };

    auto result = parser.parse(5,argv);

    auto args = std::get<AddArguments>(result);

    ASSERT_TRUE(args.deadline.has_value());
    EXPECT_EQ(args.deadline.value(),"2025-06-01");
}




   //ADD REPEATING TASK


TEST(ParserTest, AddRepeatingTask) {

    ArgumentParser parser;

    char* argv[] = {
        (char*)"todo",
        (char*)"add",
        (char*)"Workout",
        (char*)"--repeat",
        (char*)"daily",
        (char*)"--time",
        (char*)"08:00"
    };

    auto result = parser.parse(7,argv);

    auto args = std::get<AddArguments>(result);

    ASSERT_TRUE(args.repeat.has_value());
    ASSERT_TRUE(args.timeOfDay.has_value());

    EXPECT_EQ(args.repeat.value(),"daily");
    EXPECT_EQ(args.timeOfDay.value(),"08:00");
}




   //ERROR CASES


TEST(ParserTest, RepeatWithoutTimeThrows) {

    ArgumentParser parser;

    char* argv[] = {
        (char*)"todo",
        (char*)"add",
        (char*)"Task",
        (char*)"--repeat",
        (char*)"daily"
    };

    EXPECT_THROW(parser.parse(5,argv),std::invalid_argument);
}

TEST(ParserTest, TimeWithoutRepeatThrows) {

    ArgumentParser parser;

    char* argv[] = {
        (char*)"todo",
        (char*)"add",
        (char*)"Task",
        (char*)"--time",
        (char*)"08:00"
    };

    EXPECT_THROW(parser.parse(5,argv),std::invalid_argument);
}

TEST(ParserTest, UnknownCommandThrows) {

    ArgumentParser parser;

    char* argv[] = {(char*)"todo",(char*)"unknown"};

    EXPECT_THROW(parser.parse(2,argv),std::invalid_argument);
}