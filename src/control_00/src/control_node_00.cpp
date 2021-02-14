#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

class Sub_Pub{
    public:
    Sub_Pub(){
        pub_ = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);

        sub_ = nh.subscribe("/scan",1, &Sub_Pub::scannerCallback,this);
    }

    void scannerCallback(const sensor_msgs::LaserScanConstPtr &scan_msg){
        ROS_INFO("Front= [%f] Left=[%f] Right=[%f]" ,scan_msg->ranges[359],scan_msg->ranges[89],scan_msg->ranges[269]);
        cmd_msg.linear.x = 0.3;
        cmd_msg.angular.z = 0.0;
        pub_.publish(cmd_msg);

        if(scan_msg->ranges[359] < 0.800000){
                cmd_msg.linear.x = 0.1;
                cmd_msg.angular.z = 0.65;
                pub_.publish(cmd_msg);
                ROS_INFO("turn");
            }
        
        if( (0.190000 < scan_msg->ranges[269] < 0.330000)){
            cmd_msg.linear.x = 0.07;
            cmd_msg.angular.z = 0.18;
            pub_.publish(cmd_msg);
            ROS_INFO("right_wall(+)");          
        }
        else if(0.330000 <= scan_msg->ranges[269] <= 0.400000) {
            cmd_msg.linear.x = 0.3;
            pub_.publish(cmd_msg);
        }
        else if(scan_msg->ranges[269] > 0.400000){
            cmd_msg.linear.x = 0.07;
            cmd_msg.angular.z = -0.14;
            pub_.publish(cmd_msg);
            ROS_INFO("right_wall(-)");          
            
            if(scan_msg->ranges[359] < 0.800000){
                cmd_msg.linear.x = 0.05;
                cmd_msg.angular.z = 0.65;
                pub_.publish(cmd_msg);
                ROS_INFO("turn__");
            }
        }

 
    }

    private:
    ros::NodeHandle nh;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    
    geometry_msgs::Twist cmd_msg;
    
};

int main(int argc, char**argv){
    ros::init(argc, argv, "control_node_00");
    Sub_Pub SAPObject;
    ros::Rate loop_rate(100);
    ros::spin();

    return 0;
}