******************************************************
***multiplier   carry save 8x8*****
*** THIS FILE IS ONLY AN EXAMPLE OF A COMPLEX NETLIST, 
*** YOU SHOULD NOT USE THIS AS A REFERENCE TEMPLATE
*** TO SPECIFY THE NETLIST OF A MULTIPLIER
******************************************************

***.INCLUDE subcircuit/subcircuit.sp
.INCLUDE model/16nm_HP.sp
.PARAM Lmin=16n
.PARAM Wmin=16n
.PARAM ALIM=0.7

****Z0*****************************************************	
XAND0	0	1	Z0	X0N	Y0N			AND

****Z1*****************************************************	
XAND1	0	1	a0	X1N 	Y0N 			AND
XAND2	0	1	b0	X0N 	Y1N			AND
XFA0 	0	1 	nZ1 	nc1 	c0N 	b0N	a0N	FA_SUB
XNOT0   0       1       Z1      nZ1N                            NOT_MIA

****Z2*****************************************************	
XAND3	0	1	a1	X2N	Y0N			AND
XAND4	0	1	b1	X1N 	Y1N 			AND
XFA1 	0	1 	na2 	nc2 	c0N 	b1N	a1N	FA_SUB
XAND5	0	1	b2	X0N 	Y2N			AND
XNOT1   0       1       nb2     b2N                             NOT_MIA
XFA2 	0	1 	Z2 	c3 	nc1N 	nb2N	na2N	FA_SUB

****Z3*****************************************************	
XAND6	0	1	a3	X3N	Y0N 			AND
XAND7	0	1	b3	X2N 	Y1N 			AND
XFA3 	0	1 	na4 	nc4 	c0N 	b3N	a3N	FA_SUB
XAND8	0	1	b4	X1N 	Y2N 			AND
XNOT2   0       1       nb4     b4N                             NOT_MIA
XFA4 	0	1 	a5 	c5 	nc2N 	nb4N	na4N	FA_SUB
XAND9	0	1	b5	X0N 	Y3N 			AND
XFA5 	0	1 	nZ3 	nc6 	c3N 	b5N	a5N	FA_SUB
XNOT3   0       1       Z3      nZ3N                            NOT_MIA

****Z4****************************************************	
XAND10	0	1	a6	X4N	Y0N 			AND
XAND11	0	1	b6	X3N 	Y1N			AND
XFA6 	0	1 	na7 	nc7 	c0N 	b6N	a6N	FA_SUB
XAND12	0	1	b7	X2n 	Y2N			AND
XNOT4   0       1       nb7     b7N                             NOT_MIA
XFA7 	0	1 	a8 	c8 	nc4N 	nb7N	na7N	FA_SUB
XAND13	0	1	b8	X1N 	Y3N			AND
XFA8 	0	1 	na9 	nc9 	c5N 	b8N	a8N	FA_SUB
XAND14	0	1	b9	X0N 	Y4N 			AND
XNOT5   0       1       nb9     b9N                             NOT_MIA
XFA9 	0	1 	Z4 	c10 	nc6N 	nb9N	na9N	FA_SUB

****Z5*****************************************************	
XAND15	0	1	a10	X5N	Y0N			AND
XAND16	0	1	b10	X4N 	Y1N			AND
XFA10 	0	1 	na11 	nc11 	c0N 	b10N	a10N	FA_SUB
XAND17	0	1	b11	X3N 	Y2N 			AND
XNOT6   0       1       nb11    b11N                            NOT_MIA
XFA11 	0	1	a12 	c12 	nc7N 	nb11N	na11N 	FA_SUB
XAND18	0	1	b12	X2N 	Y3N 			AND
XFA12 	0	1 	na13 	nc13 	c8N 	b12N	a12N	FA_SUB
XAND19	0	1	b13	X1N 	Y4N 			AND
XNOT7   0       1       nb13    b13N                            NOT_MIA
XFA13 	0	1 	a14 	c14 	nc9N 	nb13N	na13N	FA_SUB
XAND20	0	1	b14	X0N 	Y5N 			AND
XFA14 	0	1 	nZ5 	nc15 	c10N 	b14N	a14N	FA_SUB
XNOT8   0       1       Z5      nZ5N                            NOT_MIA

****Z6*****************************************************				
XAND21	0	1	a15	X6N	Y0N 			AND
XAND22	0	1	b15	X5N 	Y1N 			AND
XFA15 	0	1 	na16 	nc16 	nc0N 	b15N	a15N	FA_SUB
XAND23	0	1	b16	X4N 	Y2N 			AND
XNOT9   0       1       nb16    b16N                            NOT_MIA
XFA16 	0	1 	a17 	c17 	nc11N 	nb16N	na16N	FA_SUB
XAND24	0	1	b17	X3N 	Y3N 			AND
XFA17 	0	1 	na18 	nc18 	c12N 	b17N	a17N	FA_SUB
XAND25	0	1	b18	X2N 	Y4N 			AND
XNOT10  0       1       nb18    b18N                            NOT_MIA
XFA18 	0	1 	a19 	c19 	nc13N 	nb18N	na18N	FA_SUB
XAND26	0	1	b19	X1N 	Y5N 			AND
XFA19 	0	1 	na20 	nc20 	c14N 	b19N	a19N	FA_SUB
XAND27	0	1	b20	X0N 	Y6N			AND
XNOT11  0       1       nb20    b20N                            NOT_MIA
XFA20 	0	1 	Z6 	c21 	c15N 	b20N	a20N	FA_SUB

****Z7*****************************************************				
XAND28	0	1	a21	X7N	Y0N			AND
XAND29	0	1	b21	X6N 	Y1N 			AND
XFA21 	0	1 	na22 	nc22 	c0N 	b21N	a21N	FA_SUB
XAND30	0	1	b22	X5N 	Y2N			AND
XNOT12  0       1       nb22    b22N                            NOT_MIA
XFA22 	0	1 	a23 	c23 	nc16N 	nb22N	na22N	FA_SUB
XAND31	0	1	b23	X4N 	Y3N 			AND
XFA23 	0	1 	na24 	nc24 	c17N 	b23N	a23N	FA_SUB
XAND32	0	1	b24	X3N 	Y4N 			AND
XNOT13  0       1       nb24    b24N                            NOT_MIA
XFA24 	0	1 	a25 	c25 	nc18N 	nb24N	na24N	FA_SUB
XAND33	0	1	b25	X2N 	Y5N 			AND
XFA25 	0	1 	na26 	nc26 	c19N 	b25N	a25N	FA_SUB
XAND34	0	1	b26	X1N 	Y6N 			AND
XNOT14  0       1       nb26    b26N                            NOT_MIA
XFA26 	0	1 	a27 	c27 	nc20N 	nb26N	na26N	FA_SUB
XAND35	0	1	b27	X0N 	Y7N			AND
XFA27 	0	1 	nZ7 	nc28 	c21N 	b27N	a27N	FA_SUB
XNOT15  0       1       Z7      nZ7                             NOT_MIA

****Z8*****************************************************				
XAND36	0	1	a28	X7N	Y1N			AND
XNOT16  0       1       na28    a28N                            NOT_MIA
XAND37	0	1	b28	X6N 	Y2N 			AND
XNOT17  0       1       nb28    b28N                            NOT_MIA
XFA28 	0	1 	a29 	c29 	nc22N 	nb28N	na28N	FA_SUB
XAND38	0	1	b29	X5N 	Y3N 			AND
XFA29 	0	1 	na30 	nc30 	c23N 	b29N	a29N	FA_SUB
XAND39	0	1	b30	X4N 	Y4N			AND
XNOT18  0       1       nb30    b30N                            NOT_MIA
XFA30 	0	1 	a31 	c31 	nc24N 	nb30N	na30N	FA_SUB
XAND40	0	1	b31	X3N 	Y5N			AND
XFA31 	0	1 	na32 	nc32 	c25N 	b31N	a31N	FA_SUB
XAND41	0	1	b32	X2N 	Y6N 			AND
XNOT19  0       1       nb32    b32N                            NOT_MIA
XFA32 	0	1 	a33 	c33 	nc26N 	nb32N	na32N	FA_SUB
XAND42	0	1	b33	X1N 	Y7N 			AND
XFA33 	0	1 	na34 	nc34 	c27N 	b33N	a33N	FA_SUB
XNOT20  0       1       nB34    B34N                            NOT_MIA
XFA34 	0	1 	Z8 	c35 	nc28N 	nB34N	na34N	FA_SUB

****Z9*****************************************************				
XAND43	0	1	a35	X7N	Y2N			AND
XAND44	0	1	b35	X6N 	Y3N 			AND
XFA35 	0	1 	na36 	nc36 	c29N 	b35N	a35N	FA_SUB
XAND45	0	1	b36	X5N 	Y4N 			AND
XNOT21  0       1       nb36    b36N                            NOT_MIA
XFA36 	0	1 	a37 	c37 	nc30N 	nb36N	na36N	FA_SUB
XAND46	0	1	b37	X4N 	Y5N			AND
XFA37 	0	1 	na38 	nc38 	c31N 	b37N	a37N	FA_SUB
XAND47	0	1	b38	X3N 	Y6N 			AND
XNOT22  0       1       nb38    b38N                            NOT_MIA
XFA38 	0	1 	a39 	c39 	nc32N 	nb38N	na38N	FA_SUB
XAND48	0	1	b39	X2N 	Y7N 			AND
XFA39 	0	1 	na40 	nc40 	c33N	b39N	a39N	FA_SUB
XNOT23  0       1       a40     na40N                           NOT_MIA
XNOT24  0       1       c34     nc34N                           NOT_MIA
XFA40 	0	1 	nZ9 	nc41 	c35N 	c34N	a40N	FA_SUB
XNOT25  0       1       Z9      nZ9N                            NOT_MIA

****Z10****************************************************		
XAND49	0	1	a41	X7N	Y3N			AND
XAND50	0	1	b41	X6N 	Y4N			AND
XNOT26  0       1       na41    a41N                            NOT_MIA
XNOT27  0       1       nb41    b41N                            NOT_MIA
XFA41 	0	1 	a42 	c42 	nc36N 	nb41N	na41N	FA_SUB
XAND51	0	1	b42	X5N 	Y5N 			AND
XFA42 	0	1 	na43 	nc43 	c37N 	b42N	a42N	FA_SUB
XAND52	0	1	b43	X4N 	Y6N 			AND
XNOT28  0       1       nb43    b43N                            NOT_MIA
XFA43 	0	1 	a44 	c44 	nc38N 	nb43N	na43N	FA_SUB
XAND53	0	1	b44	X3N 	Y7N 			AND
XFA44 	0	1 	na45 	nc45 	c39N 	b44N	a44N	FA_SUB
XFA45 	0	1 	Z10 	c46 	nc41N 	nc40N	na45N	FA_SUB	

****Z11*****************************************************				
XAND54	0	1	a46	X7N	Y4N 			AND
XAND55	0	1	b46	X6N 	Y5N 			AND
XFA46 	0	1 	na47 	nc47 	c42N 	b46N	a46N	FA_SUB
XAND56	0	1	b47	X5N 	Y6N			AND
XNOT29  0       1       nb47    b47N                            NOT_MIA
XFA47 	0	1 	a48 	c48 	nc43N 	nb47N	na47N	FA_SUB
XAND57	0	1	b48	X4N 	Y7N 			AND
XFA48 	0	1 	na49 	nc49 	c44N 	b48N	a48N	FA_SUB
XNOT30  0       1       a49     na49N                           NOT_MIA
XNOT31  0       1       c45     nc45N                           NOT_MIA
XFA49 	0	1 	nZ11 	nc50 	c46N 	c45N	a49N	FA_SUB
XNOT32  0       1       Z11     nZ11N                           NOT_MIA

****Z12*****************************************************			
XAND58	0	1	a50	X7N	Y5N 			AND
XAND59	0	1	b50	X6N 	Y6N 			AND
XNOT33  0       1       na50    a50N                            NOT_MIA
XNOT34  0       1       nb50    b50N                            NOT_MIA
XFA50 	0	1 	a51 	c51 	nc47N 	nb50N	na50N	FA_SUB
XAND60	0	1	b51	X5N 	Y7N			AND
XFA51 	0	1 	na52 	nc52 	c48N 	b51N	a51N	FA_SUB
XFA52 	0	1	Z12 	c53 	nc50N 	nc49N	na52N 	FA_SUB

****Z13*****************************************************				
XAND61	0	1	a53	X7N	Y6N 			AND
XAND62	0	1	b53	X6N 	Y7N 			AND
XFA53 	0	1 	na54 	nc54 	c51N 	b53N	a53N	FA_SUB
XNOT35  0       1       a54     na54N                           NOT_MIA
XNOT36  0       1       c52     nc52N                           NOT_MIA
XFA54 	0	1 	nZ13 	nc55 	c53N 	c52N	a54N	FA_SUB
XNOT37  0       1       Z13     nZ13N                           NOT_MIA

****Z14-Z15*************************************************
XAND63	0	1	a55	X7N 	Y7N 			AND
XNOT38  0       1       na55    a55N                            NOT_MIA
XFA55 	0	1 	Z14 	Z15 	nc55N 	nc54N	na55N	FA_SUB


********************************************************************************************
*supply******************************************************************************
VDD 1 0 dc ALIM

*carry input c0 = 0 FA -> HA
vc0 c0 0 dc 0

*HA input in final adder
vB34 B34 0 dc 0

*********************************************************************************************
*independent generators of NOISE voltage*********************************************

*primary inputs

V_noise_VX0N X0N X0 pwl (0 0 1000p 0)
V_noise_VX1N X1N X1 pwl (0 0 1000p 0)
V_noise_VX2N X2N X2 pwl (0 0 1000p 0)
V_noise_VX3N X3N X3 pwl (0 0 1000p 0)
V_noise_VX4N X4N X4 pwl (0 0 1000p 0)
V_noise_VX5N X5N X5 pwl (0 0 1000p 0)
V_noise_VX6N X6N X6 pwl (0 0 1000p 0)
V_noise_VX7N X7N X7 pwl (0 0 1000p 0)
V_noise_VY0N Y0N Y0 pwl (0 0 1000p 0)
V_noise_VY1N Y1N Y1 pwl (0 0 1000p 0)
V_noise_VY2N Y2N Y2 pwl (0 0 1000p 0)
V_noise_VY3N Y3N Y3 pwl (0 0 1000p 0)
V_noise_VY4N Y4N Y4 pwl (0 0 1000p 0)
V_noise_VY5N Y5N Y5 pwl (0 0 1000p 0)
V_noise_VY6N Y6N Y6 pwl (0 0 1000p 0)
V_noise_VY7N Y7N Y7 pwl (0 0 1000p 0)

V_noise_Vc0N     c0N     c0    pwl (0 0 1000p 0)
V_noise_VB34N    B34N    B34   pwl (0 0 1000p 0)
V_noise_VnB34N   nB34N   nB34  pwl (0 0 1000p 0)

*internal connections

V_noise_Va0N     a0N     a0    pwl (0 0 1000p 0)
V_noise_Va1N     a1N     a1    pwl (0 0 1000p 0)
V_noise_Vna2N    na2N    na2   pwl (0 0 1000p 0)
V_noise_Va3N     a3N     a3    pwl (0 0 1000p 0)
V_noise_Vna4N    na4N    na4   pwl (0 0 1000p 0)
V_noise_Va5N     a5N     a5    pwl (0 0 1000p 0)
V_noise_Va6N     a6N     a6    pwl (0 0 1000p 0)
V_noise_Vna7N    na7N    na7   pwl (0 0 1000p 0)
V_noise_Va8N     a8N     a8    pwl (0 0 1000p 0)
V_noise_Vna9N    na9N    na9   pwl (0 0 1000p 0)
V_noise_Va10N    a10N    a10   pwl (0 0 1000p 0)
V_noise_Vna11N   na11N   na11  pwl (0 0 1000p 0)
V_noise_Va12N    a12N    a12   pwl (0 0 1000p 0)
V_noise_Vna13N   na13N   na13  pwl (0 0 1000p 0)
V_noise_Va14N    a14N    a14   pwl (0 0 1000p 0)
V_noise_Va15N    a15N    a15   pwl (0 0 1000p 0)
V_noise_Vna16N   na16N   na16  pwl (0 0 1000p 0)
V_noise_Va17N    a17N    a17   pwl (0 0 1000p 0)
V_noise_Vna18N   na18N   na18  pwl (0 0 1000p 0)
V_noise_Va19N    a19N    a19   pwl (0 0 1000p 0)
V_noise_Vna20N   na20N   na20  pwl (0 0 1000p 0)
V_noise_Va21N    a21N    a21   pwl (0 0 1000p 0)
V_noise_Vna22N   na22N   na22  pwl (0 0 1000p 0)
V_noise_Va23N    a23N    a23   pwl (0 0 1000p 0)
V_noise_Vna24N   na24N   na24  pwl (0 0 1000p 0)
V_noise_Va25N    a25N    a25   pwl (0 0 1000p 0)
V_noise_Vna26N   na26N   na26  pwl (0 0 1000p 0)
V_noise_Va27N    a27N    a27   pwl (0 0 1000p 0)
V_noise_Va28N    a28N    a28   pwl (0 0 1000p 0)
V_noise_Vna28N   na28N   na28  pwl (0 0 1000p 0)
V_noise_Va29N    a29N    a29   pwl (0 0 1000p 0)
V_noise_Vna30N   na30N   na30  pwl (0 0 1000p 0)
V_noise_Va31N    a31N    a31   pwl (0 0 1000p 0)
V_noise_Vna32N   na32N   na32  pwl (0 0 1000p 0)
V_noise_Va33N    a33N    a33   pwl (0 0 1000p 0)
V_noise_Vna34N   na34N   na34  pwl (0 0 1000p 0)
V_noise_Va35N    a35N    a35   pwl (0 0 1000p 0)
V_noise_Vna36N   na36N   na36  pwl (0 0 1000p 0)
V_noise_Va37N    a37N    a37   pwl (0 0 1000p 0)
V_noise_Vna38N   na38N   na38  pwl (0 0 1000p 0)
V_noise_Va39N    a39N    a39   pwl (0 0 1000p 0)
V_noise_Vna40N   na40N   na40  pwl (0 0 1000p 0)
V_noise_Va40N    a40N    a40   pwl (0 0 1000p 0)
V_noise_Va41N    a41N    a41   pwl (0 0 1000p 0)
V_noise_Vna41N   na41N   na41  pwl (0 0 1000p 0)
V_noise_Va42N    a42N    a42   pwl (0 0 1000p 0)
V_noise_Vna43N   na43N   na43  pwl (0 0 1000p 0)
V_noise_Va44N    a44N    a44   pwl (0 0 1000p 0)
V_noise_Vna45N   na45N   na45  pwl (0 0 1000p 0)
V_noise_Va46N    a46N    a46   pwl (0 0 1000p 0)
V_noise_Vna47N   na47N   na47  pwl (0 0 1000p 0)
V_noise_Va48N    a48N    a48   pwl (0 0 1000p 0)
V_noise_Vna49N   na49N   na49  pwl (0 0 1000p 0)
V_noise_Va49N    a49N    a49   pwl (0 0 1000p 0)
V_noise_Va50N    a50N    a50   pwl (0 0 1000p 0)
V_noise_Vna50N   na50N   na50  pwl (0 0 1000p 0)
V_noise_Va51N    a51N    a51   pwl (0 0 1000p 0)
V_noise_Vna52N   na52N   na52  pwl (0 0 1000p 0)
V_noise_Va53N    a53N    a53   pwl (0 0 1000p 0)
V_noise_Vna54N   na54N   na54  pwl (0 0 1000p 0)
V_noise_Va54N    a54N    a54   pwl (0 0 1000p 0)
V_noise_Va55N    a55N    a55   pwl (0 0 1000p 0)
V_noise_Vna55N   na55N   na55  pwl (0 0 1000p 0)


V_noise_Vb0N     b0N     b0    pwl (0 0 1000p 0)
V_noise_Vb1N     b1N     b1    pwl (0 0 1000p 0)
V_noise_Vb2N     b2N     b2    pwl (0 0 1000p 0)
V_noise_Vnb2N    nb2N    nb2   pwl (0 0 1000p 0)
V_noise_Vb3N     b3N     b3    pwl (0 0 1000p 0)
V_noise_Vb4N     b4N     b4    pwl (0 0 1000p 0)
V_noise_Vnb4N    nb4N    nb4   pwl (0 0 1000p 0)
V_noise_Vb5N     b5N     b5    pwl (0 0 1000p 0)
V_noise_Vb6N     b6N     b6    pwl (0 0 1000p 0)
V_noise_Vb7N     b7N     b7    pwl (0 0 1000p 0)
V_noise_Vnb7N    nb7N    nb7   pwl (0 0 1000p 0)
V_noise_Vb8N     b8N     b8    pwl (0 0 1000p 0)
V_noise_Vb9N     b9N     b9    pwl (0 0 1000p 0)
V_noise_Vnb9N    nb9N    nb9   pwl (0 0 1000p 0)
V_noise_Vb10N    b10N    b10   pwl (0 0 1000p 0)
V_noise_Vb11N    b11N    b11   pwl (0 0 1000p 0)
V_noise_Vnb11N   nb11N   nb11  pwl (0 0 1000p 0)
V_noise_Vb12N    b12N    b12   pwl (0 0 1000p 0)
V_noise_Vb13N    b13N    b13   pwl (0 0 1000p 0)
V_noise_Vnb13N   nb13N   nb13  pwl (0 0 1000p 0)
V_noise_Vb14N    b14N    b14   pwl (0 0 1000p 0)
V_noise_Vb15N    b15N    b15   pwl (0 0 1000p 0)
V_noise_Vb16N    b16N    b16   pwl (0 0 1000p 0)
V_noise_Vnb16N   nb16N   nb16  pwl (0 0 1000p 0)
V_noise_Vb17N    b17N    b17   pwl (0 0 1000p 0)
V_noise_Vb18N    b18N    b18   pwl (0 0 1000p 0)
V_noise_Vnb18N   nb18N   nb18  pwl (0 0 1000p 0)
V_noise_Vb19N    b19N    b19   pwl (0 0 1000p 0)
V_noise_Vb20N    b20N    b20   pwl (0 0 1000p 0)
V_noise_Vnb20N   nb20N   nb20  pwl (0 0 1000p 0)
V_noise_Vb21N    b21N    b21   pwl (0 0 1000p 0)
V_noise_Vb22N    b22N    b22   pwl (0 0 1000p 0)
V_noise_Vnb22N   nb22N   nb22  pwl (0 0 1000p 0)
V_noise_Vb23N    b23N    b23   pwl (0 0 1000p 0)
V_noise_Vb24N    b24N    b24   pwl (0 0 1000p 0)
V_noise_Vnb24N   nb24N   nb24  pwl (0 0 1000p 0)
V_noise_Vb25N    b25N    b25   pwl (0 0 1000p 0)
V_noise_Vb26N    b26N    b26   pwl (0 0 1000p 0)
V_noise_Vb27N    b27N    b27   pwl (0 0 1000p 0)
V_noise_Vb28N    b28N    b28   pwl (0 0 1000p 0)
V_noise_Vnb28N   nb28N   nb28  pwl (0 0 1000p 0)
V_noise_Vb29N    b29N    b29   pwl (0 0 1000p 0)
V_noise_Vb30N    b30N    b30   pwl (0 0 1000p 0)
V_noise_Vnb30N   nb30N   nb30  pwl (0 0 1000p 0)
V_noise_Vb31N    b31N    b31   pwl (0 0 1000p 0)
V_noise_Vb32N    b32N    b32   pwl (0 0 1000p 0)
V_noise_Vnb32N   nb32N   nb32  pwl (0 0 1000p 0)
V_noise_Vb33N    b33N    b33   pwl (0 0 1000p 0)

V_noise_Vb35N    b35N    b35   pwl (0 0 1000p 0)
V_noise_Vb36N    b36N    b36   pwl (0 0 1000p 0)
V_noise_Vnb36N   nb36N   nb36  pwl (0 0 1000p 0)
V_noise_Vb37N    b37N    b37   pwl (0 0 1000p 0)
V_noise_Vb38N    b38N    b38   pwl (0 0 1000p 0)
V_noise_Vnb38N   nb38N   nb38  pwl (0 0 1000p 0)
V_noise_Vb39N    b39N    b39   pwl (0 0 1000p 0)

V_noise_Vb41N    b41N    b41   pwl (0 0 1000p 0)
V_noise_Vnb41N   nb41N   nb41  pwl (0 0 1000p 0)
V_noise_Vb42N    b42N    b42   pwl (0 0 1000p 0)
V_noise_Vb43N    b43N    b43   pwl (0 0 1000p 0)
V_noise_Vnb43N   nb43N   nb43  pwl (0 0 1000p 0)
V_noise_Vb44N    b44N    b44   pwl (0 0 1000p 0)

V_noise_Vb46N    b46N    b46   pwl (0 0 1000p 0)
V_noise_Vb47N    b47N    b47   pwl (0 0 1000p 0)
V_noise_Vnb47N   nb47N   nb47  pwl (0 0 1000p 0)
V_noise_Vb48N    b48N    b48   pwl (0 0 1000p 0)

V_noise_Vb50N    b50N    b50   pwl (0 0 1000p 0)
V_noise_Vnb50N   nb50N   nb50  pwl (0 0 1000p 0)
V_noise_Vb51N    b51N    b51   pwl (0 0 1000p 0)

V_noise_Vb53N    b53N    b53   pwl (0 0 1000p 0)


V_noise_Vnc1N     nc1N     nc1    pwl (0 0 1000p 0)
V_noise_Vnc2N     nc2N     nc2    pwl (0 0 1000p 0)
V_noise_Vc3N      c3N      c3     pwl (0 0 1000p 0)
V_noise_Vnc4N     nc4N     nc4    pwl (0 0 1000p 0)
V_noise_Vc5N      c5N      c5     pwl (0 0 1000p 0)
V_noise_Vnc6N     nc6N     nc6    pwl (0 0 1000p 0)
V_noise_Vnc7N     nc7N     nc7    pwl (0 0 1000p 0)
V_noise_Vc8N      c8N      c8     pwl (0 0 1000p 0)
V_noise_Vnc9N     nc9N     nc9    pwl (0 0 1000p 0)
V_noise_Vc10N     c10N     c10    pwl (0 0 1000p 0)
V_noise_Vnc11N    nc11N    nc11   pwl (0 0 1000p 0)
V_noise_Vc12N     c12N     c12    pwl (0 0 1000p 0)
V_noise_Vnc13N    nc13N    nc13   pwl (0 0 1000p 0)
V_noise_Vc14N     c14N     c14    pwl (0 0 1000p 0)
V_noise_Vnc15N    nc15N    nc15   pwl (0 0 1000p 0)
V_noise_Vnc16N    nc16N    nc16   pwl (0 0 1000p 0)
V_noise_Vc17N     c17N     c17    pwl (0 0 1000p 0)
V_noise_Vnc18N    nc18N    nc18   pwl (0 0 1000p 0)
V_noise_Vc19N     c19N     c19    pwl (0 0 1000p 0)
V_noise_Vnc20N    nc20N    nc20   pwl (0 0 1000p 0)
V_noise_Vc21N     c21N     c21    pwl (0 0 1000p 0)
V_noise_Vnc22N    nc22N    nc22   pwl (0 0 1000p 0)
V_noise_Vc23N     c23N     c23    pwl (0 0 1000p 0)
V_noise_Vnc24N    nc24N    nc24   pwl (0 0 1000p 0)
V_noise_Vc25N     c25N     c25    pwl (0 0 1000p 0)
V_noise_Vnc26N    nc26N    nc26   pwl (0 0 1000p 0)
V_noise_Vc27N     c27N     c27    pwl (0 0 1000p 0)
V_noise_Vnc28N    nc28N    nc28   pwl (0 0 1000p 0)
V_noise_Vc29N     c29N     c29    pwl (0 0 1000p 0)
V_noise_Vnc30N    nc30N    nc30   pwl (0 0 1000p 0)
V_noise_Vc31N     c31N     c31    pwl (0 0 1000p 0)
V_noise_Vnc32N    nc32N    nc32   pwl (0 0 1000p 0)
V_noise_Vc33N     c33N     c33    pwl (0 0 1000p 0)
V_noise_Vnc34N    nc34N    nc34   pwl (0 0 1000p 0)
V_noise_Vc34N     c34N     c34    pwl (0 0 1000p 0)
V_noise_Vc35N     c35N     c35    pwl (0 0 1000p 0)
V_noise_Vnc36N    nc36N    nc36   pwl (0 0 1000p 0)
V_noise_Vc37N     c37N     c37    pwl (0 0 1000p 0)
V_noise_Vnc38N    nc38N    nc38   pwl (0 0 1000p 0)
V_noise_Vc39N     c39N     c39    pwl (0 0 1000p 0)
V_noise_Vnc40N    nc40N    nc40   pwl (0 0 1000p 0)
V_noise_Vnc41N    nc41N    nc41   pwl (0 0 1000p 0)
V_noise_Vc42N     c42N     c42    pwl (0 0 1000p 0)
V_noise_Vnc43N    nc43N    nc43   pwl (0 0 1000p 0)
V_noise_Vc44N     c44N     c44    pwl (0 0 1000p 0)
V_noise_Vnc45N    nc45N    nc45   pwl (0 0 1000p 0)
V_noise_Vc45N     c45N     c45    pwl (0 0 1000p 0)
V_noise_Vc46N     c46N     c46    pwl (0 0 1000p 0)
V_noise_Vnc47N    nc47N    nc47   pwl (0 0 1000p 0)
V_noise_Vc48N     c48N     c48    pwl (0 0 1000p 0)
V_noise_Vnc49N    nc49N    nc49   pwl (0 0 1000p 0)
V_noise_Vnc50N    nc50N    nc50   pwl (0 0 1000p 0)
V_noise_Vc51N     c51N     c51    pwl (0 0 1000p 0)
V_noise_Vnc52N    nc52N    nc52   pwl (0 0 1000p 0)
V_noise_Vc52N     c52N     c52    pwl (0 0 1000p 0)
V_noise_Vc53N     c53N     c53    pwl (0 0 1000p 0)
V_noise_Vnc54N    nc54N    nc54   pwl (0 0 1000p 0)
V_noise_Vnc55N    nc55N    nc55   pwl (0 0 1000p 0)


V_noise_VnZ1N     nZ1N     nZ1    pwl (0 0 1000p 0)
V_noise_VnZ3N     nZ3N     nZ3    pwl (0 0 1000p 0)
V_noise_VnZ5N     nZ5N     nZ5    pwl (0 0 1000p 0)
V_noise_VnZ7N     nZ7N     nZ7    pwl (0 0 1000p 0)
V_noise_VnZ9N     nZ9N     nZ9    pwl (0 0 1000p 0)
V_noise_VnZ11N    nZ11N    nZ11   pwl (0 0 1000p 0)
V_noise_VnZ13N    nZ13N    nZ13   pwl (0 0 1000p 0)

*********************************************************************************************
*************TEST****************************************************************************

*example 11111111x11111111
*input signals 
vx0 X0 0 dc ALIM	
vx1 X1 0 dc ALIM
vx2 X2 0 dc ALIM	
vx3 X3 0 dc ALIM
vx4 X4 0 dc ALIM	
vx5 X5 0 dc ALIM
vx6 X6 0 dc ALIM	
vx7 X7 0 dc ALIM

vy0 Y0 0 dc ALIM
vy1 Y1 0 dc ALIM
vy2 Y2 0 dc ALIM
vy3 Y3 0 dc ALIM
vy4 Y4 0 dc ALIM
vy5 Y5 0 dc ALIM
vy6 Y6 0 dc ALIM
vy7 Y7 0 dc ALIM

.TRAN 1p 1000p

.control

run 
plot  Z15 Z8

.end  

