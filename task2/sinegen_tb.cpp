#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsinegen.h"

#include "vbuddy.cpp"     // include vbuddy code
#define MAX_SIM_CYC 1000000
#define ADDRESS_WIDTH 8
#define ROM_SZ 256

int main(int argc, char **argv, char **env) {
  int simcyc;     // simulation clock count
  int tick;       // each clk cycle has two ticks for two edges

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vsinegen* top = new Vsinegen;
  // init trace dump
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  tfp->open ("sinegen.vcd");
 
  // init Vbuddy
  if (vbdOpen()!=1) return(-1);
  vbdHeader("L2T1: SigGen");
  //vbdSetMode(1);        // Flag mode set to one-shot

  // initialize simulation inputs
  top->clk = 1;
  top->rst = 0;
  top->en = 1;
  top->incr = 1;

  // run simulation for MAX_SIM_CYC clock cycles
  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {
    // dump variables into VCD file and toggle clock
    for (tick=0; tick<2; tick++) {
      tfp->dump (2*simcyc+tick);
      top->clk = !top->clk;
      top->eval ();
    }
    
    top->offset = vbdValue();
    // plot ROM output and print cycle count
    vbdPlot(int (top->dout1), 0, 255);
    vbdPlot(int (top->dout2), 0, 255);
    vbdCycle(simcyc);

    // either simulation finished, or 'q' is pressed
    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
      exit(0);                // ... exit if finish OR 'q' pressed
  }

  vbdClose();     // ++++
  tfp->close(); 
  exit(0);
}

// int main (int argc, char **argv, char **env){
//     int i; //counts the number of clock cycles to simulate
//     int clk; //the module clock signal 

//     Verilated:: commandArgs (argc, argv);
//     //init top verilog instance
//     Vcounter* top = new Vcounter;  //instantiate the counter module as Vcounter which is the name of all generated files this is the DUT (device under testing)
//     //init trace dump
//     Verilated::traceEverOn (true); //turn on signal tracing and tell Verilator to dump waveform data to counter.vcd
//     VerilatedVcdC* tfp = new VerilatedVcdC; 
//     top->trace (tfp, 99); 
//     tfp->open ("counter.vcd");


//     //init Vbuddy

//     if (vbdOpen()!= 1) return (-1); 
//     vbdHeader ("Lab 1: Counter");

//     //initialize simulation inputs
//     top->clk = 1; //only top level signals are visible
//     top->rst = 1; 
//     top->en = 0; 

//     //run simulation for many clock cycles
//     for (i=0; i < 300; i++){ //for loop where simulation happens - i counts clock cycles
//         //dump vars into VCDfile and toggle clock 
//         for (clk = 0; clk < 2; clk++){ //for loop to toggle clock and outputs trace for each half of the clock cycle and forces model to evaluate on both edges of clock 
//             tfp->dump (2*i+clk);
//             top->clk = !top->clk; 
//             top->eval(); 
//         }
//         vbdPlot(int(top->count), 0, 255);
//         // Send Count value to vbuddy
//         // vbdHex(4, (int(top->count) >> 16) & 0xF);
//         // vbdHex(3, (int(top->count) >> 8) & 0xF);
//         // vbdHex(2, (int(top->count) >> 4) & 0xF);
//         // vbdHex(1, int(top->count) & 0xF);
//         vbdCycle(i+1);
    

//         //change input stimuli
//         top->rst = (i < 2) | (i==15); 
//         top->en = vbdFlag();
//         if (Verilated::gotFinish()) exit (0);
//     }

//     vbdClose();
//     tfp->close(); 
//     exit(0);
// }
