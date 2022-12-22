  .DATA                
  .ADDR x4005
  .FILL x1DBD        ;; test if the dataFILL equals to the contents of assembly

.CODE
.ADDR x0010
ADD R6, R6, #-3
