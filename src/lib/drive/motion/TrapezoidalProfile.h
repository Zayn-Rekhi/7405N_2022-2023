class TrapezoidalProfile {
    private:
        double max_vel, target;  
        double acc, dec;   
        double time_acc, time_dec, time_slew, time_total; 
    
    public:

        TrapezoidalProfile(double max_vel, double acc, double dec, double target);
        double get_acc(double time);
        double get_time_total();
};