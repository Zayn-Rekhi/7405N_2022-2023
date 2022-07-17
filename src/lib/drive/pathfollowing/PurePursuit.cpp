// //
// // Created by zayn on 8/8/21.
// //

// #include "PurePursuit.h"
// #include "../../util/math.h"
// #include <cmath>
// #include <arm_neon.h>

// #define TO_RAD(n) n * M_PI / 180
// #define TARGET_VELOCITY 200
// #define TARGET_ACCEL 50
// #define STARTING_VEL 0

// PurePursuit::PurePursuit(Odometry& odometry, double lookahead, double spacing, double tolerance, double smoothWeight) : odom(odometry), lookahead(lookahead), curIndex(0), waypoints(), spacing(spacing), tolerance(tolerance), smoothWeight(smoothWeight), dataWeight(1.0f - smoothWeight) {}

// double PurePursuit::distance(PPoint point1, PPoint point2) {
//     return hsqrt(std::pow(point2.x_ - point1.x_, 2) + std::pow(point2.y_ - point1.y_, 2));
// }


// void PurePursuit::setWaypoints(const std::vector<PPoint>& points, bool smooth) {
//     waypoints.clear();

//     for (int i = 0; i < points.size() - 1; i++) {
//         PPoint start = points.at(i);
//         PPoint end = points.at(i + 1);

//         double vx = end.x_ - start.x_;
//         double vy = end.y_ - start.y_;
//         double magnitude = hsqrt(vx * vx + vy * vy);

//         vx = (vx / magnitude) * spacing;
//         vy = (vy / magnitude) * spacing;

//         int numOfPoints = ceil(magnitude / spacing);

//         for (int j = 0; j < numOfPoints; j++) {
//             waypoints.emplace_back(start.x_ + vx * j, start.y_ + vy * j);
//         }
//     }

//     if (smooth) {
//         std::vector<PPoint> original = waypoints;
//         double change = tolerance;

//         while (change >= tolerance) {
//             change = 0.0f;

//             for (int i = 1; i < original.size() - 1; i++) {
//                 PPoint oPoint = original.at(i);   // original point
//                 PPoint& point = waypoints.at(i);  // waypoint to modify
//                 PPoint hPoint = waypoints.at(i + 1);
//                 PPoint lPoint = waypoints.at(i - 1);

//                 double auxY = point.y_;
//                 double auxX = point.x_;

//                 point.y_ += dataWeight * (oPoint.y_ - point.y_) + smoothWeight * (lPoint.y_ + hPoint.y_ - (2.0 * point.y_));
//                 change += std::abs(auxY - point.y_);

//                 point.x_ += dataWeight * (oPoint.x_ - point.x_) + smoothWeight * (lPoint.x_ + hPoint.x_ - (2.0 * point.x_));
//                 change += std::abs(auxX - point.x_);
//             }
//         }
//     }

//     waypoints.push_back(points.back());
//     waypointAmt = waypoints.size();

//     double running_distances = 0;
//     distances.push_back(running_distances);

//     for(int i = 1; i < waypoints.size(); i++) {
//         PPoint prev = waypoints.at(i - 1);
//         PPoint next = waypoints.at(i);
        
//         double dist = distance(prev, next);
//         double cur_dist = running_distances + dist;

//         distances.push_back(cur_dist);
//         running_distances += dist;
//     }

//     // printf("%d %d \n", distances.size(), waypoints.size());

//     curvatures.push_back(0.0001);
//     for(int i = 1; i < waypoints.size() - 1; i++) {
//         PPoint prev = waypoints.at(i - 1);
//         PPoint cur = waypoints.at(i);
//         PPoint next = waypoints.at(i + 1);

//         cur.x_ += 0.0001;
//         cur.y_ += 0.0001;

//         double k1 = 0.5 * (std::pow(cur.x_, 2) + std::pow(cur.y_, 2) - std::pow(prev.x_, 2) - std::pow(prev.y_, 2)) / (cur.x_ - prev.x_);
//         double k2 = (cur.y_ - prev.y_) / (cur.x_ - prev.x_);

//         double b = 0.5 * (std::pow(prev.x_, 2) - 2 * prev.x_ * k1 + std::pow(prev.y_, 2) - std::pow(next.x_, 2) + 2 * next.x_ * k1 - std::pow(next.y_, 2)) / (next.x_ * k2 - next.y_ + prev.y_ - prev.x_ * k2);
//         double a = k1 - k2 * b;
//         double r = std::sqrt(std::pow(cur.x_ - a, 2) + std::pow(cur.y_ - b, 2));

//         double curvature = 1 / r;
        
//         // printf("%d %d %d %.2f\n", i-1, i, i+1, curvature);
//         curvatures.push_back(curvature);
//     }

//     curvatures.push_back(0.0001);


//     // printf("%d %d %d \n", distances.size(), waypoints.size(), curvatures.size());

//     for(int i = 0; i < waypoints.size(); i++) {
//         double curve = curvatures.at(i);
//         double vel = 2 / curve;
//         double targetVel = TARGET_VELOCITY <= vel ? TARGET_VELOCITY : vel;
//         targetVelocity.push_back(targetVel);
//     }

//     targetVelocityAccDec.push_back(0);
//     for(int i = waypoints.size() - 2; i > 0; i--) {
//         double dist = distance(waypoints.at(i), waypoints.at(i + 1));
//         double velocity = std::sqrt(std::pow(targetVelocityAccDec.at(0), 2) + (2 * TARGET_ACCEL * dist));
//         double final_vel = targetVelocity.at(i) <= velocity ? targetVelocity.at(i) : velocity;
//         targetVelocityAccDec.insert(targetVelocityAccDec.begin(), final_vel);
//     }
    
//     targetVelocityAccDec.insert(targetVelocityAccDec.begin(), STARTING_VEL);


//     // for(int i = 0; i < targetVelocity.size(); i++) {
//     //     // printf("%.2f %.2f \n", targetVelocityAccDec.at(i), targetVelocity.at(i));
//     //     // pros::delay(50);
//     // }
//     // printf("%d %d %d %d \n", distances.size(), waypoints.size(), curvatures.size(), targetVelocity.size());
// }

// /**
//  * @brief Gets the next position for the robot to move to.
//  * @return Point - where the robot should move to
//  */
// int PurePursuit::getClosestIndex(Point curPos) {
//     int index = 0;
//     double temp = 10000000;

//     for (int i = curIndex; i < waypoints.size(); i++) {
//         const PPoint& potential = waypoints.at(i);
//         double dist = distance(curPos, potential);

//         if (dist < temp) {
//             temp = dist;
//             index = i;
//         }
//     }

//     curIndex = index;
//     return index;
// }

// int PurePursuit::getClosestIndexNeon(PPoint curPos) {
//     int loops = waypoints.size() / 4;
//     int closest = 10000000;
//     int closestIdx = 0;

//     // cords of curPos into a vector
//     float32x4x2_t base;
//     base = vld2q_lane_f32((float32_t*)&curPos, base, 0);
//     base = vld2q_lane_f32((float32_t*)&curPos, base, 1);
//     base = vld2q_lane_f32((float32_t*)&curPos, base, 2);
//     base = vld2q_lane_f32((float32_t*)&curPos, base, 3);

//     float32x4x2_t data; // the x, y, heading of 4 points
//     float32x4_t distances; // distances calculated

//     PPoint* pData = waypoints.data();
//     for (int i = 0; i < loops; i++) {
//         data = vld2q_f32((float32_t*)(pData + i * 4));
//         data.val[0] = vsubq_f32(data.val[0], base.val[0]);
//         data.val[0] = vmulq_f32(data.val[0], data.val[0]);

//         data.val[1] = vsubq_f32(data.val[1], base.val[1]);
//         data.val[1] = vmulq_f32(data.val[1], data.val[1]);

//         distances = vaddq_f32(data.val[0], data.val[1]);
//         distances = vrsqrteq_f32(distances);
//         distances = vrecpeq_f32(distances);

//         #pragma GCC push_options
//         #pragma GCC unroll 4
//         for (int j = 0; j < 4; j++) {
//             float32_t dist = vgetq_lane_f32(distances, j);
//             if (dist < closest) {
//                 closest = dist;
//                 closestIdx = i * 4 + j;
//             }
//         }

//         #pragma GCC pop_options
//     }

//     // handles the rest of the elements when it can't be vectorized
//     // meaning that 
//     for (int i = loops * 4; i < waypoints.size(); i++) {
//         const PPoint& potential = waypoints.at(i);
//         double dist = distance(curPos, potential);
        
//         if (dist < closest) {
//             closest =  dist;
//             closestIdx = i;
//         }
//     }

//     return closestIdx;
// }

// Point PurePursuit::calcActLookAhead(Point curPos, int closestPointIndex) {
//     Point lookahead = curPos;
//     for (int i = closestPointIndex + 1; i < waypoints.size(); i++) {
//         int startPoint = i - 1;
//         int endPoint = i;

//         Point potential = getLookAhead(startPoint, endPoint, curPos);
//         if (potential != curPos) {
//             lookahead = potential;
//             break;
//         }
//     }

//     return lookahead;
// }


// Point PurePursuit::getLookAhead(int prev_index, int next_index, Point curPos) {
//     const PPoint& prev = waypoints.at(prev_index);
//     const PPoint& next = waypoints.at(next_index);

//     // Describes direction from start to end (vector)
//     double dx = next.x_ - prev.x_; 
//     double dy = next.y_ - prev.y_;

//     // Describes from center to start position (vector)
//     double fx = prev.x_ - curPos.x_;
//     double fy = prev.y_ - curPos.y_;

//     double a = dx * dx + dy * dy;
//     double b = 2 * (fx * dx + fy * dy);
//     double c = (fx * fx + fy * fy) - std::pow(lookahead, 2);
//     double discriminant = b * b - 4 * a * c;

//     if(discriminant < 0) {
//         return curPos;
//     } else {
//         discriminant = std::sqrt(discriminant);
//         double t1 = (-b - discriminant) / (2 * a);
//         double t2 = (-b + discriminant) / (2 * a);

//         if(t1 >= 0 && t1 <= 1) {
//             double px = prev.x_ + t1 * dx;
//             double py = prev.y_ + t1 * dy;
//             return Point(px, py);
//         }

//         if(t2 >= 0 && t2 <= 1) {
//             double px = prev.x_ + t2 * dx;
//             double py = prev.y_ + t2 * dy;
//             return Point(px, py);
//         }

//         return curPos;
//     }

// } 


// double PurePursuit::getCurve(Point curPos, Point lookaheadPos) {
//     double angle = curPos.heading_;

//     double a = -std::tan(angle); 
//     double b = 1;
//     double c = std::tan(angle) * curPos.y_ - curPos.x_; 

//     double x = std::abs(a * lookaheadPos.y_ + b * lookaheadPos.x_ + c) / std::sqrt(std::pow(a, 2) + std::pow(b, 2)); // 
//     double side = sign(std::sin(angle) * (lookaheadPos.y_ - curPos.y_) - std::cos(angle) * (lookaheadPos.x_ - curPos.x_));

//     return side * ((2 * x) / std::pow(lookahead, 2));
// }