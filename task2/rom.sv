module rom #(
    parameter ADDRESS_WDITH = 8,
              DATA_WIDTH = 8
)(
    input logic clk, 
    input logic [ADDRESS_WDITH-1:0] addr1,
    input logic [ADDRESS_WDITH-1:0] addr2,  
    output logic [DATA_WIDTH-1:0] dout1,
    output logic [DATA_WIDTH-1:0] dout2
);

logic [DATA_WIDTH-1:0] rom_array [2**ADDRESS_WDITH-1:0];

initial begin 
    $display("Loading rom.");
    $readmemh("sinerom.mem", rom_array);
end; 

always_ff @(posedge clk) begin
    //output is synchronous
    dout1 <= rom_array[addr1];
    dout2 <= rom_array[addr2];
end

endmodule





















// module sreg4 (
//     input logic clk, 
//     input logic rst, 
//     input logic data_in, 
//     input logic data_out, 
// );

//     logic [4:1] sreg; 

//     always_ff @ (posedge clk)
//         if (rst)
//             sreg <= 4'b0;
//         else begin
//             sreg[4] <= sreg[3]; 
//             sreg[3] <= sreg[2];
//             sreg[2] <= sreg[1];
//             sreg[1] <= data_in; 
//         end
//     assign data_out = sreg[4]; 
// endmodule

