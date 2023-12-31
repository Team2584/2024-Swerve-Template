#include "Robot.h"
#include "AprilTagBasedSwerve.h"
#include "Constants/SwerveConstants.h"

/**
 * This class inherits from the base SwerveDrive class, but adds the functionality of calculating odometry using the photonvision library, a camera, and april tags
 */
class SwerveDriveAutonomousController
{
private:
    SwerveDrive *baseSwerveDrive = NULL; /* A reference to our base swerve drive template. */
    AprilTagSwerve *photonTagSwerve = NULL; /* A reference to our photonlib swerve drive template. */
    PID xPIDController, yPIDController, rotationPIDController; /* PID Controllers to move in various directions */
    queue<pathplanner::PathPlannerTrajectory> trajectoryQueue; /* Queue of trajectories initialized and prepared to run */
    pathplanner::PathPlannerTrajectory currentTrajectory;  /* current trajectory in use */
    Timer trajectoryTimer; /* tracks time spent in current trajectory*/

public:
    SwerveDriveAutonomousController(SwerveDrive *swerveDrive);
    SwerveDriveAutonomousController(AprilTagSwerve *swerveDrive);

private:
    void CalculatePIDToPose(PoseEstimationType poseEstimationType, Pose2d target, double speeds[3], bool PIDsComplete[3]);
    void ResetPIDLoop();

public:
    void BeginDriveToPose();
    bool DriveToPose(Pose2d target, PoseEstimationType poseEstimationType);
    void ResetTrajectoryQueue();
    void LoadTrajectory(string trajectoryString);
    void BeginNextTrajectory();
    bool FollowTrajectory(PoseEstimationType poseEstimationType);
};