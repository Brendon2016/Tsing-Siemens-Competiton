// Generated by gencpp from file kinova_msgs/AddPoseToCartesianTrajectoryResponse.msg
// DO NOT EDIT!


#ifndef KINOVA_MSGS_MESSAGE_ADDPOSETOCARTESIANTRAJECTORYRESPONSE_H
#define KINOVA_MSGS_MESSAGE_ADDPOSETOCARTESIANTRAJECTORYRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace kinova_msgs
{
template <class ContainerAllocator>
struct AddPoseToCartesianTrajectoryResponse_
{
  typedef AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> Type;

  AddPoseToCartesianTrajectoryResponse_()
    {
    }
  AddPoseToCartesianTrajectoryResponse_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }






  typedef boost::shared_ptr< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> const> ConstPtr;

}; // struct AddPoseToCartesianTrajectoryResponse_

typedef ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<std::allocator<void> > AddPoseToCartesianTrajectoryResponse;

typedef boost::shared_ptr< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse > AddPoseToCartesianTrajectoryResponsePtr;
typedef boost::shared_ptr< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse const> AddPoseToCartesianTrajectoryResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace kinova_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'kinova_msgs': ['/home/h/catkin_ws/src/kinova-ros/kinova_msgs/msg', '/home/h/catkin_ws/devel/share/kinova_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "kinova_msgs/AddPoseToCartesianTrajectoryResponse";
  }

  static const char* value(const ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
";
  }

  static const char* value(const ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct AddPoseToCartesianTrajectoryResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::kinova_msgs::AddPoseToCartesianTrajectoryResponse_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // KINOVA_MSGS_MESSAGE_ADDPOSETOCARTESIANTRAJECTORYRESPONSE_H
