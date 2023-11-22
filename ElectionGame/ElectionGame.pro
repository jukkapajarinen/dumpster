TEMPLATE = subdirs

SUBDIRS += \
    Course \
    Student \
    TestAgent

Student.depends = Course
TestAgent.depends = Student
