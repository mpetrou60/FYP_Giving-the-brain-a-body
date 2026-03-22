% putty 2 = data with ava, avb, etc.  
data = readmatrix("putty2.csv");
n = data(4:end,1);
clock = data(4:end,2);
mv_fwd = data(4:end,3);
mv_coil = data(4:end,4);
reset = data(4:end,5);
avx = data(4:end,6);
dxn = data(4:end,7);
vxn = data(4:end,8);
ava = data(4:end,6);
avb = data(4:end,7);
drn = data(4:end,8);
dtn = data(4:end,6);
vrn = data(4:end,7);
vtn = data(4:end,8);
i = data(4:end,9);
dm = data(4:end,10);
vm = data(4:end,11);

figure(1)
plot(clock)
title("clock")

figure(2)
plot(mv_fwd)
title("mv_fwd")

figure(3)
plot(mv_coil)
title("mv_coil")

figure(4)
plot(reset)
title("reset")

figure(5)
plot(avx)
title("avx")

figure(6)
plot(dxn)
title("dxn")

figure(7)
plot(vxn)
title("vxn")

figure(8)
plot(ava)
title("ava")

figure(9)
plot(avb)
title("avb")

figure(10)
plot(drn)
title("drn")

figure(11)
plot(dtn)
title("dtn")

figure(12)
plot(vrn)
title("vrn")

figure(13)
plot(vtn)
title("vtn")