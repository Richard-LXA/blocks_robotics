#pragma once
#include <vector>
#include "./eigen3/Eigen/Dense"
#include <string>

#define heightWaypoint 670

#define MAX_my(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;
using namespace Eigen;

struct PosStruct
{
	double x;				// x坐标，单位mm
	double y;				// y坐标，单位mm
	double z;				// z坐标，单位mm
	double yaw;				// yaw坐标，单位度
	double pitch;			// pitch坐标，单位度
	double roll;			// roll坐标，单位度
};

class CHLMotionPlan
{
private:
	double mJointAngleBegin[6];					//起始点位的关节角度,单位度
	double mJointAngleEnd[6];					//结束点位的关节角度，单位度
	double mStartMatrixData[16];				//起始点位的转换矩阵数组
	double mEndMatrixData[16];					//结束点位的转换矩阵数组
	double mSampleTime;							//采样点位，单位S
	double mVel;								//速度，单位m/s
	double mAcc;								//加速度，单位m/s/s
	double mDec;								//减速度，单位m / s / s
	bool mConfig[3];							//机器人姿态

	double start_pitch;
	double start_yaw;
	double start_roll;
	double end_pitch;
	double end_yaw;
	double end_roll;

	double to[6];
	double t01[6];
	double t12[6];

	double tb[6];
	double tb0[6];
	double tb1[6];
	double tb2[6];

	double v[6];
	double v01[6];
	double v12[6];

	double td[3];
	double a[6];
	double as[6];
	double ae[6];
	double aw[6];
	vector<PosStruct> Point;

public:
	CHLMotionPlan();
	virtual ~CHLMotionPlan();

	void SetSampleTime(double sampleTime);		//设置采样时间
	void SetPlanPoints(PosStruct startPos, PosStruct endPos);		//输入起始点位和结束点位的笛卡尔坐标
	void SetProfile(double vel, double acc, double dec);			//设置运动参数，速度、加速度和减速度
	void GetPlanPoints();											//关节空间梯形速度规划
	void GetPlanPoints_line(int part_num);       								//笛卡尔空间直线轨迹梯形速度规划
	void LFPB_Planning(double pos_start, double pos_end, int index);

};