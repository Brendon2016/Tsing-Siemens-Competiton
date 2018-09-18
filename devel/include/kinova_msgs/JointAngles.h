// Generated by gencpp from file kinova_msgs/JointAngles.msg
// DO NOT EDIT!


#ifndef KINOVA_MSGS_MESSAGE_JOINTANGLES_H
#define KINOVA_MSGS_MESSAGE_JOINTANGLES_H


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
struct JointAngles_
{
  typedef JointAngles_<ContainerAllocator> Type;

  JointAngles_()
    : joint1(0.0)
    , joint2(0.0)
    , joint3(0.0)
    , joint4(0.0)
    , joint5(0.0)
    , joint6(0.0)
    , joint7(0.0)  {
    }
  JointAngles_(const ContainerAllocator& _alloc)
    : joint1(0.0)
    , joint2(0.0)
    , joint3(0.0)
    , joint4(0.0)
    , joint5(0.0)
    , joint6(0.0)
    , joint7(0.0)  {
  (void)_alloc;
    }



   typedef float _joint1_type;
  _joint1_type joint1;

   typedef float _joint2_type;
  _joint2_type joint2;

   typedef float _joint3_type;
  _joint3_type joint3;

   typedef float _joint4_type;
  _joint4_type joint4;

   typedef float _joint5_type;
  _joint5_type joint5;

   typedef float _joint6_type;
  _joint6_type joint6;

   typedef float _joint7_type;
  _joint7_type joint7;




  typedef boost::shared_ptr< ::kinova_msgs::JointAngles_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::kinova_msgs::JointAngles_<ContainerAllocator> const> ConstPtr;

}; // struct JointAngles_

typedef ::kinova_msgs::JointAngles_<std::allocator<void> > JointAngles;

typedef boost::shared_ptr< ::kinova_msgs::JointAngles > JointAnglesPtr;
typedef boost::shared_ptr< ::kinova_msgs::JointAngles const> JointAnglesConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::kinova_msgs::JointAngles_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::kinova_msgs::JointAngles_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::kinova_msgs::JointAngles_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::kinova_msgs::JointAngles_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kinova_msgs::JointAngles_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kinova_msgs::JointAngles_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kinova_msgs::JointAngles_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kinova_msgs::JointAngles_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::kinova_msgs::JointAngles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bf16c4e5154848a0767d1aaab0a4796b";
  }

  static const char* value(const ::kinova_msgs::JointAngles_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xbf16c4e5154848a0ULL;
  static const uint64_t static_value2 = 0x767d1aaab0a4796bULL;
};

template<class ContainerAllocator>
struct DataType< ::kinova_msgs::JointAngles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "kinova_msgs/JointAngles";
  }

  static const char* value(const ::kinova_msgs::JointAngles_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::kinova_msgs::JointAngles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 joint1\n\
float32 joint2\n\
float32 joint3\n\
float32 joint4\n\
float32 joint5\n\
float32 joint6\n\
float32 joint7\n\
";
  }

  static const char* value(const ::kinova_msgs::JointAngles_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::kinova_msgs::JointAngles_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.joint1);
      stream.next(m.joint2);
      stream.next(m.joint3);
      stream.next(m.joint4);
      stream.next(m.joint5);
      stream.next(m.joint6);
      stream.next(m.joint7);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct JointAngles_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::kinova_msgs::JointAngles_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::kinova_msgs::JointAngles_<ContainerAllocator>& v)
  {
    s << indent << "joint1: ";
    Printer<float>::stream(s, indent + "  ", v.joint1);
    s << indent << "joint2: ";
    Printer<float>::stream(s, indent + "  ", v.joint2);
    s << indent << "joint3: ";
    Printer<float>::stream(s, indent + "  ", v.joint3);
    s << indent << "joint4: ";
    Printer<float>::stream(s, indent + "  ", v.joint4);
    s << indent << "joint5: ";
    Printer<float>::stream(s, indent + "  ", v.joint5);
    s << indent << "joint6: ";
    Printer<float>::stream(s, indent + "  ", v.joint6);
    s << indent << "joint7: ";
    Printer<float>::stream(s, indent + "  ", v.joint7);
  }
};

} // namespace message_operations
} // namespace ros

#endif // KINOVA_MSGS_MESSAGE_JOINTANGLES_H