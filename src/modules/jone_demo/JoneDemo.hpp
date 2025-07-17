//
// Created by CoCo on 7/17/2025.
//
#ifndef PX4_JONEDEMO_HPP
#define PX4_JONEDEMO_HPP

#include <px4_platform_common/module.h>
#include <px4_platform_common/module_params.h>
#include <px4_platform_common/px4_work_queue/ScheduledWorkItem.hpp>
#include <controllib/block/Block.hpp>
#include <perf/perf_counter.h>


class JoneDemo: public ModuleBase<JoneDemo>, public control::SuperBlock,
                public ModuleParams, public px4::ScheduledWorkItem{
    public:
        JoneDemo();
        ~JoneDemo() override;

        /** @see ModuleBase */
        static int task_spawn(int argc, char *argv[]);

        /** @see ModuleBase */
        static int custom_command(int argc, char *argv[]);

        /** @see ModuleBase */
        static int print_usage(const char *reason = nullptr);

        bool init();

    private:
        void Run() override;
        void parameters_update(bool force);
        perf_counter_t _cycle_perf{perf_alloc(PC_ELAPSED, MODULE_NAME": cycle time")};
};

#endif
