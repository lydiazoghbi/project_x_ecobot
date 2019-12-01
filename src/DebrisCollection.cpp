 /*
  *
  * Copyright 2019 Lydia Zoghbi and Ryan Bates.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  */
/**
 *  @file       DebrisCollection.cpp
 *  @author     Lydia Zoghbi
 *  @copyright  Copyright Apache 2.0 License
 *  @date       11/25/2019
 *  @version    1.0
 *
 *  @brief      Implementation class of DebrisCollection class
 *
 */

#include <vector>
#include "ros/ros.h"
#include "DebrisCollection.hpp"
#include <Point.hpp>
#include <string>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/image_encodings.h"
#include "sensor_msgs/Image.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Class constructor
DebrisCollection::DebrisCollection() {
  // do publishing and subscribing
//  ros::NodeHandle nh;
  sub = nh.subscribe("/camera/rgb/image_raw", 500, &DebrisCollection::imageRGBCallback, this);
  odomSub = nh.subscribe("/odom", 500, &DebrisCollection::odometryCallback, this);
  ROS_INFO_STREAM("Subscriptions made.");
  ros::Rate loop_rate(1);
  while (ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
  }
}

// Reading image from the robot's camera
// TODO: make return void
void DebrisCollection::imageRGBCallback(const sensor_msgs::ImageConstPtr& message) {
  ROS_INFO_STREAM("Entered image callback");
  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(message, sensor_msgs::image_encodings::BGR8);
  } catch (cv_bridge::Exception& e)
  {
  // TODO: error processing
ROS_INFO_STREAM("Error");
  }
  cv::imshow("Window", cv_ptr->image);
  ROS_INFO_STREAM("Image should be displayed");
  cv::waitKey(1);
  
  //if (we want image) {
  //  detectDebris(image);
  //}
}

void DebrisCollection::odometryCallback(const nav_msgs::Odometry::ConstPtr& message) {
//  message->pose.pose.
  ROS_INFO_STREAM("Bot is at " << message->pose.pose.position.x << ", " << message->pose.pose.position.y);
}


// Reading depth information from the robot's camera
std::vector<double> DebrisCollection::DepthCallback(const sensor_msgs::Image &) {}

// Applying HSV filter to detect debrid
cv::Mat DebrisCollection::Filter() {}

// Function for detecting debris after applying filter
Point DebrisCollection::detectDebris(cv::Mat filteredImage) {}

// Function for concatenating debris information if detected
void DebrisCollection::addDebris(Point detectedDebris) {}

// Function for removing debris from list after it is scooped
void DebrisCollection::removeDebris() {}

// Sorting the debris by closest to bin 
std::vector<Point> DebrisCollection::sortDebrisLocation(std::vector<Point> * debrisLocations) {}

