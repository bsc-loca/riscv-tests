import targets
import testlib

class sargantana_hart(targets.Hart):
    xlen = 64
    ram = 0x80000000
    ram_size = 0x40000000
    bad_address = ram - 8
    instruction_hardware_breakpoint_count = 0
    reset_vectors = [0x100]
    link_script_path = "sargantana.lds"
    misa = 0x8000000000341129

class sargantana(targets.Target):
    harts = [sargantana_hart()]
    openocd_config_path = "sargantana.cfg"
    timeout_sec = 180
    implements_custom_test = True
    freertos_binary = "bin/RTOSDemo64.axf"
    support_unavailable_control = True
    supports_clint_mtime = False
    invalid_memory_returns_zero = True
    support_manual_hwbp = False
    test_semihosting = False
    support_memory_sampling = False

    def create(self):
        return testlib.VerilatorSim(sim_cmd=self.sim_cmd, debug=False)
    