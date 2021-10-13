#include "convex_polygon_library/utilities.h"
#include "gtest/gtest.h"
#include <random>

std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

TEST(SimpleUtilities, EuclideanDistance) 
{
    Point p1 = {0,0};
    Point p2 = {3,4};

    EXPECT_EQ(5.0, EuclideanDistance(p1,p2));

    std::uniform_real_distribution<double> distribution(-20.0, 20.0);

    for (size_t iter; iter < 10000; ++iter)
    {
        Point pRandom1(distribution(gen), distribution(gen));
        Point pRandom2(distribution(gen), distribution(gen));

        EXPECT_LE(0.0, EuclideanDistance(pRandom1, pRandom2));
        EXPECT_EQ(0.0, EuclideanDistance(pRandom1, pRandom1));
    }
}

TEST(SimpleUtilities, DotProduct)
{
    Vector p1 = {0,0};
    Vector p2 = {3,4};

    EXPECT_EQ(0.0, p1*p2);

    Vector p3 = {2,1};

    EXPECT_EQ(10.0, p2*p3);
}

TEST(SimpleUtilities, Normalize_error)
{
    Vector p0 = {0,0};

    EXPECT_THROW({
        try
        {
            p0.Normalize();
        }
        catch (std::runtime_error const& ex)
        {
            // and this tests that it has the correct message
            EXPECT_STREQ("Attempted to normalize a point", ex.what());
            throw;
        }
    }, std::runtime_error);
}

TEST(SimpleUtilities, Normalize)
{
    Vector p1(3,4);
    p1.Normalize();
    
    Vector p1_normalized(3/5.0, 4/5.0);

    ASSERT_NEAR(p1.x, p1_normalized.x, 1e-6);
    ASSERT_NEAR(p1.y, p1_normalized.y, 1e-6);
}

TEST(SimpleUtilities, CheckPointsCollinear_positive)
{
    Point p1 = {0,0};
    Point p2 = {1,1};
    Point p3 = {2,2};
    Point p4 = {3,3};

    std::vector<Point> pointsForConvexHull = {p1,p2,p3,p4};

    ASSERT_TRUE(CheckPointsCollinear(pointsForConvexHull));
}

TEST(SimpleUtilities, CheckPointsCollinear_negative)
{
    Point p1 = {0,0};
    Point p2 = {1,1};
    Point p3 = {2,2};
    Point p4 = {3,4};

    std::vector<Point> pointsForConvexHull = {p1,p2,p3,p4};

    ASSERT_FALSE(CheckPointsCollinear(pointsForConvexHull));
}

TEST(SimpleUtilities, ThreePointOrientation_clockwise)
{
    Point P(2.1,-1.0);
    Point Q(-1.0,0.0);
    Point R(2.0,-0.5);
    ASSERT_EQ(ThreePointOrientation(P,Q,R),1);
}

TEST(SimpleUtilities, ThreePointOrientation_counterclockwise)
{
    Point P(2.5,3.3);
    Point Q(3.5,4.5);
    Point R(3.7,6.1);
    ASSERT_EQ(ThreePointOrientation(P,Q,R),2);
}

TEST(SimpleUtilities, ThreePointOrientation_collinear)
{
    Point P(0.0,0.5);
    Point Q(1.0,0.8);
    Point R(2.0,1.1);
    ASSERT_EQ(ThreePointOrientation(P,Q,R),0);
}

TEST(SimpleUtilities, ThreePointOrientation_error)
{
    Point P(0.8,0.5);
    Point Q(0.8,0.5);
    Point R(2.0,1.1);
    EXPECT_THROW({
        try
        {
            ThreePointOrientation(P,Q,R);
        }
        catch (std::invalid_argument const& ex)
        {
            // and this tests that it has the correct message
            EXPECT_STREQ("Attempted to compute the orientation of three points when at least two of them are identical", ex.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(SimpleUtilities, IsPointRightToTheEdge_clockwise)
{
    Point P(2.1,-1.0);
    Point Q(-1.0,0.0);
    Point R(2.0,-0.5);
    ASSERT_TRUE(ThreePointOrientation(P,Q,R));
}

TEST(SimpleUtilities, IsPointRightToTheEdge_counterclockwise)
{
    Point P(2.5,3.3);
    Point Q(3.5,4.5);
    Point R(3.7,6.1);
    ASSERT_TRUE(ThreePointOrientation(P,Q,R));
}

TEST(SimpleUtilities, IsPointRightToTheEdge_collinear)
{
    Point P(0.0,0.5);
    Point Q(1.0,0.8);
    Point R(2.0,1.1);
    ASSERT_FALSE(ThreePointOrientation(P,Q,R));
}

TEST(SimpleUtilities, IsPointRightToTheEdge_error)
{
    Point P(0.8,0.5);
    Point Q(0.8,0.5);
    Point R(2.0,1.1);
    EXPECT_THROW({
        try
        {
            IsPointRightToTheEdge(P,Q,R);
        }
        catch (std::invalid_argument const& ex)
        {
            // and this tests that it has the correct message
            EXPECT_STREQ("Attempted to compute the orientation of three points when at least two of them are identical", ex.what());
            throw;
        }
    }, std::invalid_argument);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
