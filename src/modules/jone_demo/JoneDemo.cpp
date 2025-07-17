//
// Created by CoCo on 7/17/2025.
//


#include "JoneDemo.hpp"
#include <chrono>
using namespace std::chrono_literals;

JoneDemo::JoneDemo() :
        SuperBlock(nullptr, "MPC"),
        ModuleParams(nullptr),
        ScheduledWorkItem(MODULE_NAME, px4::wq_configurations::nav_and_controllers){
}



JoneDemo::~JoneDemo()
{
    perf_free(_cycle_perf);
}

bool JoneDemo::init()
{
    ScheduleNow();
    return true;
}

void JoneDemo::parameters_update(bool force) {
    return;
}
void JoneDemo::Run()
{
    if (should_exit()) {

        exit_and_cleanup();
        return;
    }

    // reschedule backup
    ScheduleDelayed(100);

    parameters_update(false);

    perf_begin(_cycle_perf);

    printf("hello jone\r\n");

    perf_end(_cycle_perf);
}


int JoneDemo::task_spawn(int argc, char *argv[])
{
    JoneDemo *instance = new JoneDemo();

    if (instance) {
        _object.store(instance);
        _task_id = task_id_is_work_queue;

        if (instance->init()) {
            return PX4_OK;
        }

    } else {
        PX4_ERR("alloc failed");
    }

    delete instance;
    _object.store(nullptr);
    _task_id = -1;

    return PX4_ERROR;
}


int JoneDemo::custom_command(int argc, char **argv) {
    return print_usage("unknown command");
}




int JoneDemo::print_usage(const char *reason)
{
    if (reason) {
        PX4_WARN("%s\n", reason);
    }

    PRINT_MODULE_DESCRIPTION(
            R"DESCR_STR(
### Description
  jone demo
)DESCR_STR");

    PRINT_MODULE_USAGE_NAME("jone_demo", "controller");
    PRINT_MODULE_USAGE_COMMAND("start");
    PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

    return 0;
}

// PX4 默认约定是：
// 模块名（这里是 jone_demo）+ _main 组成入口函数名

extern "C" __EXPORT int jone_demo_main(int argc, char *argv[])
{
    return JoneDemo::main(argc, argv);
}






