/*
 * Copyright (c) 2012, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ORK_TABLE_DISPLAY_H
#define ORK_TABLE_DISPLAY_H

#include <rviz/message_filter_display.h>

#include <rviz/properties/color_property.h>

#include <object_recognition_msgs/TableArray.h>

namespace object_recognition_ros
{

class OrkTableVisual;

// OrkTableDisplay will display a mesh for an object as well as its pose
// through a TF
class OrkTableDisplay: public rviz::MessageFilterDisplay<object_recognition_msgs::TableArray>
{
  Q_OBJECT
public:
  // Constructor.  pluginlib::ClassLoader creates instances by calling
  // the default constructor, so make sure you have one.
  OrkTableDisplay();

  // Overrides of protected virtual functions from Display.  As much
  // as possible, when Displays are not enabled, they should not be
  // subscribed to incoming data and should not show anything in the
  // 3D view.  These functions are where these connections are made
  // and broken.
protected:
  virtual void
  onInitialize();

  // A helper to clear this display back to the initial state.
  virtual void
  reset();
private Q_SLOTS:
  void updateColor();
private:
  // Function to handle an incoming ROS message.
  void
  processMessage(const object_recognition_msgs::TableArrayConstPtr& msg);

  /** Storage for the list of visuals */
  std::vector<boost::shared_ptr<OrkTableVisual> > visuals_;

  /** flag indicating whether the hull should be displayed */
  rviz::BoolProperty *do_display_hull_;
  /** flag indicating whether the bounding box should be displayed */
  rviz::BoolProperty *do_display_bounding_box_;
  /** flag indicating whether the table top should be displayed */
  rviz::BoolProperty *do_display_top_;
  /** color of the tables */
  rviz::ColorProperty *table_color_;
};

}

#endif // ORK_TABLE_DISPLAY_H
