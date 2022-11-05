module sigdelay #(
    parameter A_WIDTH = 9,
              D_WIDTH = 8
)(
    //interface signals
    input logic clk, 
    input logic rst, 
    input logic en, 
    input logic rd, 
    input logic wr, 
    input logic [D_WIDTH-1:0] mic_signal, 
    input logic [A_WIDTH-1:0] incr,
    input logic [D_WIDTH-1:0] offset,
    output logic [D_WIDTH-1:0] dout
);

    logic [A_WIDTH-1:0] address; 

counter addrCounter (
    .clk (clk), 
    .rst (rst),
    .en (en), 
    .incr (incr), 
    .count (address)
);

ram sineRam (
    .clk (clk), 
    .wr_en (wr), 
    .rd_en (rd), 
    .wr_addr (address + offset), 
    .rd_addr (address), 
    .dout (dout),
    .din (mic_signal)
);

endmodule


