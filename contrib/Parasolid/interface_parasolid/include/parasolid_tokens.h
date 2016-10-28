/*
  Parasolid Tokens

  Copyright 2013 Siemens Product Lifecycle Management Software Inc. All rights reserved.
  This software and related documentation are proprietary to 
  Siemens Product Lifecycle Management Software Inc.

*/

#ifndef PARASOLID_TOKENS_H_INCLUDED
#define PARASOLID_TOKENS_H_INCLUDED

#define NULTAG    0 /* value for a null tag */

#define KI_TRUE   1 /* KI_cod_logical value for true */
#define KI_FALSE  0 /* KI_cod_logical value for false */

#define TYEN00   1000 /* entity type <base> */
#define TYENGE   1001 /* geometry entity */
#define TYENTO   1002 /* topology entity */
#define TYENAD   1003 /* assoc data entity */
#define TYGE00   2000 /* geometry type <base> */
#define TYGEPT   2001 /* point */
#define TYGECU   2002 /* curve */
#define TYGESU   2003 /* surface */
#define TYGETF   2004 /* transform */
#define TYPT00   2500 /* point type <base> */
#define TYPTCA   2501 /* cartesian point */
#define TYCU00   3000 /* curve type <base> */
#define TYCUST   3001 /* straight */
#define TYCUCI   3002 /* circle */
#define TYCUEL   3003 /* ellipse */
#define TYCUIN   3004 /* intersection-curve */
#define TYCUPA   3005 /* parametric-curve */
#define TYCUSP   3006 /* sp-curve */
#define TYCUFG   3007 /* foreign curve */
#define TYCUCP   3008 /* constant parm curve */
#define TYCUTR   3009 /* trimmed curve */
#define TYSU00   4000 /* surface type <base> */
#define TYSUPL   4001 /* plane */
#define TYSUCY   4002 /* cylinder */
#define TYSUCO   4003 /* cone */
#define TYSUSP   4004 /* sphere */
#define TYSUTO   4005 /* torus */
#define TYSUPA   4006 /* parametric-surface */
#define TYSUBL   4007 /* blending-surface */
#define TYSUOF   4008 /* offset-surface */
#define TYSUSE   4009 /* swept-surface */
#define TYSUSU   4010 /* swung-surface */
#define TYSUFG   4011 /* foreign surface */
#define TYBL00   4600 /* blending sub types <base> */
#define TYBL1B   4601 /* non_overlapped */
#define TYBL2S   4602 /* 2 overlapping same sense */
#define TYBL2D   4603 /* 2 overlapping different sense */
#define TYBL3S   4604 /* 3 overlapping same sense */
#define TYBL3D   4605 /* 3 overlapping different sense */
#define TYTO00   5000 /* topology type <base> */
#define TYTOVX   5001 /* vertex */
#define TYTOED   5002 /* edge */
#define TYTOLO   5003 /* loop */
#define TYTOFA   5004 /* face */
#define TYTOSH   5005 /* shell */
#define TYTOBY   5006 /* body */
#define TYTOIN   5007 /* instance */
#define TYTOAS   5008 /* assembly */
#define TYTOWO   5009 /* world */
#define TYTOFN   5010 /* fin */
#define TYTORG   5011 /* region */
#define TYAS00   5050 /* assembly type <base> */
#define TYASCL   5051 /* collective assembly */
#define TYIN00   5070 /* instance type <base> */
#define TYINPS   5071 /* positive instance */
#define TYAD00   6000 /* assoc data type <base> */
#define TYADAT   6001 /* attribute */
#define TYADLI   6002 /* list */
#define TYADAD   6003 /* attribute definition */
#define TYADFE   6005 /* feature */
#define TYAT00   7000 /* attribute type <base> */
#define TYATSY   7001 /* system attribute */
#define TYATUS   7002 /* user attribute */
#define TYFE00  12000 /* feature type <base> */
#define TYFEFA  12001 /* face feature */
#define TYFEED  12002 /* edge feature */
#define TYFEVX  12003 /* vertex feature */
#define TYFESU  12004 /* surface feature */
#define TYFECU  12005 /* curve feature */
#define TYFEPT  12006 /* point feature */
#define TYFEMX  12007 /* mixed feature */
#define TYFEIN  12008 /* instance feature */
#define TYFERG  12009 /* region feature */
#define TYSA00   8000 /* system attribute type <base> */
#define TYSACO   8001 /* colour attribute */
#define TYSABL   8002 /* blend attribute */
#define TYSAHA   8003 /* hatch attribute */
#define TYSADN   8004 /* density attribute */
#define TYSAPL   8005 /* plines attribute */
#define TYSAHU   8006 /* Bezier hull attribute */
#define TYSARG   8013 /* regions attribute */
#define TYSARF   8014 /* reflectivity attribute */
#define TYSATR   8015 /* translucency attribute */
#define TYSANM   8017 /* name */
#define TYSABE   8018 /* V5 blend attribute */
#define TYSAFG   8019 /* FG not found attribute */
#define TYSADF   8020 /* Deleted rubber faces */
#define TYSAPH   8021 /* Planar hatch attribute */
#define TYSABN   8022 /* V9 blend attribute */
#define TYSARD   8023 /* Region density */
#define TYSAFD   8024 /* Face density */
#define TYSAED   8025 /* Edge density */
#define TYSAVD   8026 /* Vertex density */
#define TYSARH   8027 /* Radial hatch attribute */
#define TYSAUH   8028 /* Parametric hatch attribute */
#define TYSATY   8029 /* transparency attribute */
#define TYSAIF   8030 /* incremental facetting attribute */
#define TYSAFV   8031 /* facet vertex data attribute */
#define TYSAEN   8032 /* edge no merge attribute */
#define TYSAPF   8033 /* polygonal face attribute */
#define TYSAPE   8034 /* polygonal edge attribute */
#define TYSAFE   8035 /* facet vertex edge data attribute */
#define TYSAFF   8036 /* facet vertex fin data attribute */
#define TYSAGM   8037 /* group merge attribute */
#define TYSAUN   8038 /* Unicode name attribute */
#define TYSAGC   8039 /* group control attribute */
#define TYSAC2   8040 /* colour 2 attribute */
#define TYSAT2   8041 /* translucency 2 attribute */
#define TYSALA   8042 /* layer attribute */
#define TYSAIV   8043 /* invisible attribute */
#define TYSABI   8044 /* blend identification attribute */
#define TYUA00   9000 /* user attribute type <base> */
#define TYLI00  10000 /* list type <base> */
#define TYLIIN  10001 /* integer list */
#define TYLIRL  10002 /* real list */
#define TYLITG  10003 /* tag list */
#define TYOWNR  13000 /* pseudo-type owner <base> */
#define RQAC00   5800 /* attribute class <base> */
#define RQAC01   5801 /* attribute class 1 */
#define RQAC02   5802 /* attribute class 2 */
#define RQAC03   5803 /* attribute class 3 */
#define RQAC04   5804 /* attribute class 4 */
#define RQAC05   5805 /* attribute class 5 */
#define RQAC06   5806 /* attribute class 6 */
#define RQAC07   5807 /* attribute class 7 */
#define RQAP00   5900 /* attribute property <base> */
#define RQAPIN   5901 /* integer property */
#define RQAPRL   5902 /* real property */
#define RQAPCS   5903 /* character property */
#define RQAPVC   5904 /* vector property */
#define RQAPCO   5905 /* coordinate property */
#define RQAPDR   5906 /* direction property */
#define RQAPAX   5907 /* axis property */
#define ENVE00   5100 /* vertex property <base> */
#define ENVEIS   5101 /* isolated vertex */
#define ENVESP   5102 /* spur vertex */
#define ENVEWR   5103 /* wire vertex */
#define ENVENO   5104 /* normal vertex */
#define ENED00   5300 /* edge property <base> */
#define ENEDOW   5301 /* open wire edge */
#define ENEDON   5302 /* open normal edge */
#define ENEDCN   5303 /* closed normal edge */
#define ENEDCW   5304 /* closed wire edge */
#define ENEDRN   5305 /* ring normal edge */
#define ENEDOB   5306 /* open biwire edge */
#define ENEDCB   5307 /* closed biwire edge */
#define ENEDRB   5308 /* ring biwire edge */
#define ENLO00   5400 /* loop property <base> */
#define ENLOHO   5401 /* hole loop */
#define ENLOPE   5402 /* peripheral loop */
#define ENLONA   5403 /* loop not hole or peripheral */
#define ENSH00   5500 /* shell property <base> */
#define ENSHSO   5501 /* solid shell */
#define ENSHVO   5502 /* void shell */
#define ENSHSH   5503 /* sheet shell */
#define ENSHWR   5504 /* wire shell */
#define ENBY00   5600 /* body property <base> */
#define ENBYSO   5601 /* solid body */
#define ENBYSH   5602 /* sheet body */
#define ENBYMN   5603 /* minimum body */
#define ENBYWR   5604 /* wire body */
#define ENBYGN   5605 /* general body */
#define ENWR00   5620 /* wire property <base> */
#define ENWRGN   5621 /* general wire */
#define ENWRPA   5622 /* parametric wire */
#define ENSE00   5640 /* sheet property <base> */
#define ENSEGN   5641 /* general sheet */
#define ENSEPA   5642 /* parametric sheet */
#define ENST00   5660 /* part state <base> */
#define ENSTST   5661 /* stored part */
#define ENSTMD   5662 /* modified part */
#define ENSTNW   5663 /* new part */
#define ENSTAN   5664 /* anonymous part */
#define ENSTUN   5665 /* unloaded part */
#define ENCL00   5700 /* enclosure <base> */
#define ENCLIN   5701 /* inside */
#define ENCLOU   5702 /* outside */
#define ENCLON   5703 /* on (the limits of) */
#define SLIP00      0 /* interface parameter <base> */
#define SLIPCH      1 /* argument checking */
#define SLIPJO      2 /* journalling */
#define SLIPBB      3 /* bulletin board */
#define SLIPRB      5 /* rollback */
#define SLIPBT      6 /* binary transmit/receive */
#define SLIPLC      7 /* local checking */
#define SLIPUF      8 /* receive user-fields */
#define SLIPSN      9 /* binary snapshot */
#define SLIPSI     10 /* self intersection checking */
#define SLIPCG     11 /* obsolete */
#define SLIPCO     12 /* continuity checking */
#define SLIPPA     13 /* obsolete */
#define SLIPDC     14 /* data checking */
#define SLIPTL     15 /* tag limit */
#define SLIPGS     16 /* create generated surfaces */
#define SLIPRF     17 /* roll forward */
#define SLIPGT     18 /* create generalised topology */
#define SLMP00      0 /* modelling parameter <base> */
#define SLMPLP      1 /* linear precision */
#define SLMPAP      2 /* angular precision */
#define SLAB00      0 /* reason for abort <base> */
#define SLABUI      1 /* user interrupt */
#define SLABRE      2 /* run-time error */
#define SLABFE      3 /* Frustrum error */
#define SLER00  13100 /* error enquiry <base> */
#define SLERRO  13101 /* routine */
#define SLEREC  13102 /* error code */
#define SLEREX  13103 /* explanation */
#define SLERAR  13104 /* argument */
#define SLERAI  13105 /* array index */
#define SLERLE  13106 /* list entry */
#define SLERTG  13107 /* tag */
#define SLST00  13200 /* state enquiry <base> */
#define SLSTAR  13201 /* at rollmark */
#define SLSTNF  13202 /* nsteps forward */
#define SLSTNB  13203 /* nsteps back */
#define SLSTVM  13204 /* virtual memory */
#define SLSTFS  13205 /* free space */
#define SLSTMT  13206 /* max tag */
#define SLLO00  13300 /* local op. action <base> */
#define SLLOCP  13301 /* cap */
#define SLLOGR  13302 /* grow */
#define SLLOGP  13303 /* grow from parent */
#define SLLORB  13304 /* leave rubber */
#define SLLOGS  13305 /* grow or shrink */
#define SLLOLI  13306 /* Heal loops independently */
#define SLLOLT  13307 /* Heal loops together */
#define RTLO00  13400 /* local op. return <base> */
#define RTLOOK  13401 /* body is ok */
#define RTLONG  13402 /* body was negative */
#define RTLOSX  13403 /* self-intersecting */
#define SLFI00  13500 /* file enquiry <base> */
#define SLFIVN  13501 /* modeller version */
#define SLCP00  13600 /* control point type <base> */
#define SLCPBS  13601 /* bspline */
#define SLCPBZ  13602 /* bezier */
#define SLCPSP  13603 /* spline */
#define SLBA00  13650 /* parametric basis <base> */
#define SLBAHE  13651 /* hermite */
#define SLBABZ  13652 /* bezier */
#define SLBAPY  13653 /* polynomial */
#define SLBATA  13654 /* taylor series */
#define SLLE00  13680 /* simplification level <base> */
#define SLLEGL  13681 /* global simplification */
#define SLLELO  13682 /* local simplification */
#define SLPK00  13690 /* pick return <base> */
#define SLPKIR  13691 /* pick along infinite ray */
#define SLPKSR  13692 /* pick along semi infinite ray */
#define RROP00      0 /* rendering option <base> */
#define RROPED      1 /* render edges */
#define RROPRH      2 /* render radial hatch */
#define RROPPH      3 /* render planar hatch */
#define RROPUB      4 /* render unfixed blends */
#define RROPSI      5 /* render silhouettes */
#define RROPIV      6 /* render invisible lines */
#define RROPTR      7 /* render transformed entities */
#define RROPPS      8 /* perspective view */
#define RROPSM      9 /* distinguish smooth edges */
#define RROPSF     11 /* surface reflectivity */
#define RROPBK     12 /* background */
#define RROPFC     13 /* face colour */
#define RROPAN     15 /* anti-alias */
#define RROPDM     18 /* depth modulation */
#define RROPRG     19 /* regions */
#define RROPRA     20 /* regions by attribute */
#define RROPIS     21 /* distinguish image smoothness */
#define RROPPA     22 /* render parametric hatch */
#define RROPTL     23 /* render translucent faces */
#define RROPCT     24 /* curve tolerances */
#define RROPCV     25 /* polygon convexity */
#define RROPFS     26 /* facet size */
#define RROPHO     27 /* holes permitted  */
#define RROPNF     28 /* no fitting */
#define RROPPT     29 /* planarity tolerances */
#define RROPST     30 /* surface tolerances */
#define RROPVN     31 /* output vertex normals */
#define RROPET     32 /* output edge tags */
#define RROPIE     33 /* render internal edges */
#define RROPIN     34 /* distinguish internal edges */
#define RROPPC     35 /* render parametric curves */
#define RROPVM     36 /* match facet vertices */
#define RROPDR     37 /* render drafting lines */
#define RROPHR     38 /* hierarchical output */
#define RROPHN     39 /* hierarchical output no geometry */
#define RROPFI     40 /* facet with infinite view dependency */
#define RROPFP     41 /* facet with perspective view dependency */
#define RROPTS     42 /* facet strips */
#define RROPNC     43 /* render nurbs curves */
#define RROPMF     44 /* minimum facet size */
#define RROPPI     45 /* parameter information */
#define RROPDS     46 /* drafting / smooth edges behaviour */
#define RROPHP     47 /* hierarchical output parametrised */
#define RROPVP     48 /* use viewport */
#define RROPAS     49 /* analytic silhouettes */
#define RROPD1     50 /* first derivatives at facet vertices */
#define RROPD2     51 /* first and second derivatives at facet vertices */
#define RROPIL     52 /* ignore loops */
#define RROPSD     53 /* silhouette density */
#define PAPR00  13700 /* parametric prop <base> */
#define PAPRPE  13701 /* periodic */
#define PAPRNP  13702 /* non periodic */
#define PAPRCS  13703 /* clamped start */
#define PAPRCE  13704 /* clamped end */
#define PAPRTL  13705 /* clamped top left twist vec */
#define PAPRTR  13706 /* clamped top right twist vec */
#define PAPRBL  13707 /* clamped bottom left twist */
#define PAPRBR  13708 /* clamped bottom right twist */
#define PAPRDS  13709 /* degenerate start */
#define PAPRDE  13710 /* degenerate end */
#define PAPRAM  13711 /* amalgamate knot vectors */
#define PAPRKT  13712 /* knot vector supplied */
#define PAPRNS  13713 /* natural start */
#define PAPRNE  13714 /* natural end */
#define PAPRUP  13715 /* u-parameter */
#define PAPRVP  13716 /* v-parameter */
#define PAPRPU  13717 /* periodic in u */
#define PAPRPV  13718 /* periodic in v */
#define PAPRIS  13719 /* insert null seg in start cu */
#define PAPRIE  13720 /* insert null seg in end cu */
#define PAPRCU  13721 /* force cubic lofting */
#define PAPREX  13722 /* exact representation */
#define PAPRNB  13723 /* natural bottom */
#define PAPRNT  13724 /* natural top */
#define PAPRNL  13725 /* natural left */
#define PAPRNR  13726 /* natural right */
#define PAPRCB  13727 /* clamped bottom */
#define PAPRCT  13728 /* clamped top */
#define PAPRCL  13729 /* clamped left */
#define PAPRCR  13730 /* clamped right */
#define PAPRKU  13731 /* u knot vector supplied */
#define PAPRKV  13732 /* v knot vector supplied */
#define PAPRIF  13733 /* infinite */
#define PAPRXT  13734 /* extendable */
#define PAPRNX  13735 /* not extendable */
#define PAPRDP  13736 /* periodic not cont. diff */
#define PAPRCN  13737 /* continuous */
#define PAPRDC  13738 /* discontinuous */
#define PAPRLI  13739 /* linear */
#define PAPRCI  13740 /* circular */
#define PAPRDG  13741 /* degenerate */
#define PAPRSD  13742 /* derv. start curve supplied */
#define PAPRED  13743 /* derv. end curve supplied */
#define PAPRSW  13744 /* degen. start curve supplied */
#define PAPREW  13745 /* degen. end curve supplied */
#define PAPRBC  13746 /* bounds coincident */
#define RTST00  13800 /* return state <base> */
#define RTSTNG  13801 /* body is inside out */
#define RTSTCR  13802 /* data structure corrupt */
#define RTSTMG  13803 /* missing geometry */
#define RTSTSX  13804 /* self-intersecting topology */
#define RTSTGX  13805 /* self-intersecting geometry */
#define RTSTDG  13806 /* degenerate geometry */
#define RTSTIN  13807 /* inconsistent geom & topol */
#define RTSTIG  13808 /* invalid geometry */
#define RTSTSZ  13809 /* size settings differ */
#define RTSTBX  13810 /* size box violation */
#define RTSTCF  13812 /* failure in checking attempt */
#define RTSTWG  13813 /* withdrawn geometry types */
#define RTSTMD  13814 /* consistency mending enacted */
#define RTSTIO  13815 /* body was inside out */
#define RTSTFF  13816 /* face-face inconsistency */
#define RTSTOC  13817 /* open curve on ring edge */
#define RTSTVC  13818 /* vertex not on curve */
#define RTSTER  13819 /* edge reversed */
#define RTSTSP  13820 /* SP-curves of edge not within edge tolerance */
#define RTSTVT  13821 /* vertices touch */
#define RTSTVS  13822 /* vertex not on surface */
#define RTSTES  13823 /* edge not on surface */
#define RTSTEO  13824 /* edges incorrectly ordered at vertex */
#define RTSTMV  13825 /* missing vertex at surface singularity */
#define RTSTLC  13826 /* loops inconsistent */
#define RTSTGC  13827 /* geometry not G1-continuous */
#define RTSTSH  13828 /* inconsistent shells */
#define RTSTFC  13829 /* checker failure during face-face check */
#define RTSTEF  13830 /* illegal edge-face intersection */
#define RTSTEE  13831 /* illegal edge-edge intersection */
#define RTSTFO  13832 /* faces out of order around edge */
#define RTSTSG  13833 /* shell geometry and topology inconsistent */
#define RTSTAC  13834 /* acorn shell clashes with another shell */
#define RTSTRS  13835 /* regions of body are inconsistent */
#define RTSTID  13836 /* invalid or duplicate identifiers */
#define RTSTON  13837 /* open nominal geometry on ring edge */
#define RTSTVN  13838 /* vertex not on nominal geometry */
#define RTSTSN  13839 /* SP curves of edge not within tolerance of nominal geometry */
#define RTSTRN  13840 /* nominal geometry in wrong direction for edge */
#define RTSTAN  13841 /* attribute definition has illegal name */
#define RTSTAS  13842 /* attribute has illegal string field */
#define RTSTAT  13843 /* attribute is invalid */
#define RTSTDL  13844 /* attribute has field of bad length */
#define RTSTBU  13845 /* attribute has illegal Unicode string field */
#define RTSTBB  13846 /* attribute has out of range byte field */
#define RTSTEM  13847 /* attribute has empty required field */
#define RTSTBI  13848 /* attribute has out of range integer field */
#define RTSTNU  13849 /* attribute has non unit vector where one is required */
#define RTSTBR  13850 /* attribute has out of range real field */
#define RTSTSB  13851 /* attribute has out of range short field */
#define RTSTPV  13852 /* attribute has out of range position vector */
#define SROP00  13900 /* standard rep opt <base> */
#define SROPCU  13901 /* output cubics */
#define SROPNR  13902 /* output non-rationals */
#define SROPBS  13903 /* use a B-spline sf approx */
#define SROPCT  13904 /* supply curve tolerance */
#define SROPCN  13905 /* loops unconfined and not continuous */
#define SROPCY  13906 /* loops confined and not continuous */
#define SROPCC  13907 /* loops confined, continuous, closed */
#define SROPCP  13908 /* loops confined, continuous, closed, exactly one periphery */
#define SROPID  13909 /* include degeneracies in trim curves */
#define SROPED  13910 /* exclude degeneracies from trim curves */
#define SROPNG  13911 /* output associated geometry */
#define SROPNT  13912 /* output associated topology */
#define SROPNE  13913 /* don't extend surface to fit SP-curves */
#define MAOP00  14000 /* masspr option <base> */
#define MAOPNA  14001 /* no amount properties */
#define MAOPAM  14002 /* amount and mass */
#define MAOPCG  14003 /* centre of gravity */
#define MAOPIN  14004 /* moment of inertia */
#define MAOPNP  14005 /* no periphery data */
#define MAOPPE  14006 /* periphery required */
#define MAOPNE  14007 /* no error estimates */
#define MAOPEM  14008 /* modulus of errors given */
#define MAOPEI  14009 /* error intervals given */
#define MAOPCS  14010 /* treat entity members as complete solid */
#define OUFO00  14100 /* output format <base> */
#define OUFOPV  14101 /* position vector */
#define OUFODR  14102 /* unit direction  */
#define OUFOAX  14103 /* axis: base + direction */
#define OUFONP  14104 /* null position */
#define OUFOCU  14120 /* curve pointer */
#define OUFOSU  14121 /* surface pointer */
#define ATOP00  14200 /* attribute definition options <base> */
#define ATOPOW  14201 /* legal owner type codes */
#define ATOPFL  14202 /* field types */
#define ATOPCL  14203 /* class code */
#define MDOP00  14300 /* mending option <base> */
#define MDOPMD  14301 /* consistency mend */
#define MDOPRB  14302 /* rubberize stranded topology */
#define MDOPNG  14304 /* negate inside-out bodies */
#define BBEV00  14400 /* bulletin board event <base> */
#define BBEVCR  14401 /* create event */
#define BBEVDE  14402 /* delete event */
#define BBEVCH  14403 /* change event */
#define BBEVSP  14404 /* split event */
#define BBEVME  14405 /* merge event */
#define BBEVTR  14406 /* transfer event */
#define BBEVCO  14407 /* copy event */
#define BBEVTF  14408 /* transform event */
#define BBEVAC  14409 /* attribute change event */
#define BBOP00  14500 /* bulletin board option <base> */
#define BBOPOF  14501 /* switch off */
#define BBOPON  14502 /* switch on for tags */
#define BBOPUF  14503 /* switch on for tags and user fields */
#define CICL00  14610 /* curve intersect classification <base> */
#define CICLSI  14611 /* simple intersection */
#define CICLTG  14612 /* tangency */
#define CICLSC  14613 /* start of coincidence */
#define CICLEC  14614 /* end of coincidence */
#define CLOP00  14700 /* closest approach option <base> */
#define CLOPPT  14701 /* specify point close to solution */
#define CLOPPR  14702 /* specify parameter estimates */
#define CLOPUP  14703 /* specify upper distance bound */
#define CLOPLW  14704 /* specify lower distance bound */
#define CLOPTL  14705 /* specify distance tolerance */
#define CLOPB1  14706 /* supply parameter box - 1st entity */
#define CLOPB2  14707 /* supply parameter box - 2nd entity */
#define CLOPP1  14708 /* supply parameter estimate - 1st entity */
#define CLOPP2  14709 /* supply parameter estimate - 2nd entity */
#define CLOPFA  14710 /* find all local minima */
#define CFCL00  14800 /* curve face classification <base> */
#define CFCLSI  14801 /* simple intersection */
#define CFCLTG  14802 /* touch intersection */
#define CFCLEF  14803 /* curve entering face */
#define CFCLLF  14804 /* curve leaving face */
#define CFCLEB  14805 /* curve entering boundary */
#define CFCLLB  14806 /* curve leaving boundary */
#define CFCLEI  14807 /* curve entering interior */
#define CFCLLI  14808 /* curve leaving interior */
#define CFCLTI  14809 /* tangent to inside of edge */
#define CFCLTO  14810 /* tangent to outside of edge */
#define CFCLUC  14811 /* unclassified */
#define CFCLSC  14812 /* curve enters at start of coi */
#define CFCLEC  14813 /* curve leaves at end of coi */
#define IMOP00  14900 /* imprinting opt <base> */
#define IMOPNT  14901 /* no imprinting on tool */
#define IMOPOA  14902 /* imprint bounds of overlap */
#define IMOPEF  14903 /* extend face list on target */
#define IDOP00  15000 /* identify region option <base> */
#define IDOPUN  15001 /* simulated unite */
#define IDOPIN  15002 /* simulated intersect */
#define IDOPSU  15003 /* simulated subtract */
#define IDOPFS  15004 /* selected facesets */
#define RTTO00  15100 /* CRTOBY returns <base> */
#define RTTOOK  15101 /* input is ok */
#define RTTOBB  15102 /* bad body id */
#define RTTODE  15103 /* duplicate entry */
#define RTTOUC  15104 /* undefined child */
#define RTTODC  15105 /* duplicate child */
#define RTTOWC  15106 /* wrong type of child */
#define RTTOFC  15107 /* too few children */
#define RTTOMC  15108 /* too many children */
#define RTTOWP  15109 /* wrong type of parents */
#define RTTOFP  15110 /* too few parents */
#define RTTOMP  15111 /* too many parents */
#define RTTODW  15112 /* disconnected wire */
#define RTTOIL  15113 /* invalid loop */
#define RTTOCS  15114 /* connected shells */
#define RTTODS  15115 /* disjoint shell */
#define RTTONM  15116 /* non-manifold vertex */
#define BYTY00  15200 /* body types <base> */
#define BYTYSO  15201 /* solid body */
#define BYTYSH  15202 /* sheet body */
#define BYTYWR  15203 /* wire body */
#define BYTYMN  15204 /* minimal body */
#define BYTYSS  15205 /* solid or sheet body */
#define PADI00  15300 /* parametric discontinuties <base> */
#define PADIG1  15301 /* G1 discontinuities */
#define RTCL00  15400 /* closest approach return <base> */
#define RTCLNO  15401 /* non-orthogonal to entity */
#define RTCLPD  15402 /* positive distance from entity */
#define RTCLND  15403 /* negative distance from entity */
#define RTCLON  15404 /* on entity - zero distance */
#define RTCLRS  15405 /* regional (non-unique) solution */
#define RTCLLB  15406 /* distance less than lower bound */
#define RTCLUB  15407 /* distance greater than upper bound */
#define RTMD00  15500 /* mending return <base> */
#define RTMDMS  15501 /* mend successful */
#define RTMDMF  15502 /* mend failed */
#define MDFA00  15600 /* mending return <base> */
#define MDFAFE  15601 /* faulty edge */
#define MDFANI  15602 /* non-intersecting geometry */
#define MDFAFM  15603 /* failure during mend */
#define MDFARF  15604 /* rubber face */
#define MDFACS  15605 /* coincident surfaces */
#define MDFANS  15606 /* non-intersecting surfaces */
#define RTKN00  15700 /* knitting return <base> */
#define RTKNOK  15701 /* knit successful */
#define RTKNIN  15702 /* knit incomplete */
#define CBOP00  15800 /* crbyge option <base> */
#define CBOPUR  15801 /* U parameter range */
#define CBOPVR  15802 /* V parameter range */
#define BOOP00  15900 /* bopbys option <base> */
#define BOOPIN  15901 /* intersect */
#define BOOPSU  15902 /* subtract */
#define BOOPUN  15903 /* unite */
#define BOOPEF  15904 /* extend facelist */
#define BOOPEC  15905 /* exclude boundary facesets */
#define BOOPIC  15906 /* include boundary facesets */
#define BOOPME  15907 /* merge */
#define BOOPSX  15908 /* stop self-intersections */
#define BOOPTS  15909 /* trim with sheet */
#define BOOCSH  15910 /* none of the instanced tools clash with each other */
#define BOOINF  15911 /* none of the instanced tools clash with outer loop of target face */
#define BOOCLP  15912 /* list of loops on target face that need to be tested */
#define BOOPPS  15913 /* prune solid regions of the result */
#define BOOPPV  15914 /* prune void regions of the result */
#define BOOPPU  15915 /* punch sheet */
#define BLEC00  16000 /* blecre option <base> */
#define BLECRI  16001 /* draw ribs */
#define BLECDF  16002 /* draw/fix  */
#define BLECPR  16003 /* propagate */
#define BLECTL  16004 /* set tolerance */
#define BLECLI  16005 /* linear radius variation */
#define BLECSM  16006 /* smooth */
#define BLECCL  16007 /* cliff_edge */
#define BLECCR  16008 /* circular crossection */
#define BLECCH  16009 /* linear crossection */
#define BLECSC  16010 /* same convexity cliff overflow */
#define BLECEC  16011 /* end of edge cliff overflows */
#define BLECNS  16012 /* no smooth overflows */
#define BLECNC  16013 /* no cliff edge overflows  */
#define BLECNN  16014 /* no notch overflows */
#define BLCC00  16050 /* blechk option <base> */
#define BLCCSN  16051 /* ends at singularity */
#define BLCCOT  16052 /* unsupported old type */
#define BLCCMX  16053 /* vertex too complex */
#define BLCCRS  16054 /* adjoining face is rubber */
#define BLCCRE  16055 /* truncating face is rubber */
#define BLCCTV  16056 /* illegal two edge vertex */
#define BLCCHM  16057 /* edge unsuitable for chamfer */
#define BLCCXT  16058 /* require extension of B-surf */
#define BLCCIR  16059 /* inconsistent ranges */
#define BLCCIT  16060 /* inconsistent types */
#define BLCCAB  16061 /* adjoining edge not blended */
#define BLCCOL  16062 /* completely overlaps edge loop */
#define BLCCOB  16063 /* overlapping blends */
#define BLCCOU  16064 /* overlaps unblended edge */
#define BLCCUN  16065 /* unspecified numerical problem */
#define BLCCUE  16066 /* unspecified problem at end */
#define BLCCRL  16067 /* range too large */
#define BLCCOE  16068 /* illegal overlap at end */
#define BLCCIE  16069 /* illegal end boundary */
#define BLCCIX  16070 /* cannot intersect chamfers */
#define BLCCEX  16071 /* end overlaps unblended edge */
#define BLCCOI  16072 /* illegal blend on another edge */
#define BLCCTN  16073 /* on tangent edge */
#define BLCCIP  16074 /* inconsistent cliffedge parameters */
#define INOP00  16100 /* insusu option <base> */
#define INOPBX  16101 /* Box of intersection supplied */
#define INOPPF  16102 /* Parameter box of intersection supplied for surface/face 1 */
#define INOPPS  16103 /* Box of intersection supplied for surface/face 2 */
#define INOPSI  16104 /* Return all intersections through given point */
#define INOPBP  16105 /* Return single intersection between given 2 points */
#define CROP00  16200 /* crrvsu option <base> */
#define CROPPR  16201 /* supply parameter range */
#define CROPSI  16202 /* Simplify surface */
#define SICL00  14650 /* surface intersect classification <base> */
#define SICLSI  14651 /* simple intersection */
#define SICLTG  14652 /* tangency */
#define SICLBC  14653 /* boundary of region of coincidence */
#define TSOP00  16300 /* trimmed surface check option <base> */
#define TSOPWR  16301 /* check for wire topology */
#define TSOPSX  16302 /* check for self-intersections */
#define TSOPLC  16303 /* check loops for consistency */
#define RTTS00  16400 /* trimmed surface state code <base> */
#define RTTSOK  16401 /* all checks successful */
#define RTTSFR  16402 /* redundant face with respect to tolerances */
#define RTTSCI  16403 /* loops of curves inconsistent directions */
#define RTTSSX  16404 /* edges intersect at position other than vertex */
#define RTTSLI  16405 /* invalid loop combination for surface type */
#define RTTSEO  16406 /* edges incorrectly ordered at vertex */
#define IDTY00  16500 /* common connection type <base> */
#define IDTYCS  16501 /* common curves of surfaces */
#define IDTYSC  16502 /* common surfaces of curve */
#define IDTYEF  16503 /* common edges of faces */
#define CHOP00  16600 /* chcken option <base> */
#define CHOPCR  16601 /* check for corrupt datastructure */
#define CHOPIG  16602 /* check for invalid or self-intersecting geometry */
#define CHOPED  16603 /* check for inconsistencies in edges */
#define CHOPFA  16604 /* check for inconsistencies in faces */
#define CHOPSX  16605 /* check for self-intersecting faces */
#define CHOPLC  16606 /* check for loop consistency of faces */
#define CHOPBX  16607 /* check for size-box violations */
#define CHOPFF  16608 /* check for face-face inconsistencies */
#define CHOPSH  16609 /* check for inside-out or inconsistent shells */
#define CHOPPV  16610 /* force self-intersection tests on Pre-V5 b-geometry */
#define CHOPNO  16611 /* no options, force all appropriate checks to the geometry */
#define SLTR00  16700 /* trimsh option <base> */
#define SLTRKE  16701 /* select regions to remain on the sheet */
#define SLTRRE  16702 /* select regions to be deleted from the sheet */
#define SLTRTL  16703 /* enable closing of loop gaps to optional tolerance */
#define SHOP00  16800 /* sharen option <base> */
#define SHOPIC  16801 /* only process local intersection curve relationships */
#define LOCH00  16900 /* local checking level <base> */
#define LOCHNC  16901 /* no local checking */
#define LOCHFA  16902 /* local face checking only */
#define LOCHFC  16903 /* full local checking including face-face checking */
#define RTOF00  17000 /* offset operations return <base> */
#define RTOFOK  17001 /* body is ok */
#define RTOFSO  17002 /* surface failed to offset */
#define RTOFVM  17003 /* failed to find geometry for new vertex */
#define RTOFEM  17004 /* failed to find geometry for new edge */
#define RTOFTL  17005 /* supplied edge tolerance too large */
#define RTOFVT  17009 /* edge should have disappeared */
#define RTOFNG  17013 /* offset body was negative */
#define RTOFFA  17014 /* face checking failed */
#define RTOFSX  17015 /* self-intersecting, face-face checking failed */
#define RTOFED  17016 /* edge degenerates */
#define RTOFSS  17017 /* failed to find side surface */
#define RTOFSC  17018 /* failed to find side curve */
#define PFOP00  17100 /* enpifa option <base> */
#define PFOPLO  17101 /* only consider specified loops */
#define RTTL00  17200 /* retlen status <base> */
#define RTTLOK  17201 /* replace tolerance successful */
#define RTTLNT  17202 /* tolerance not altered at near tangency */
#define RTTLMG  17203 /* could not replace tol due to missing geometry */
#define RTTLRF  17204 /* tolerance replacement by re-intersection failed */
#define TRSH00  17300 /* trshcu option <base> */
#define TRSHPD  17301 /* project curves in given direction */
#define TRSHTR  17302 /* trim as well as imprint */
#define TRSHLC  17303 /* keep region to left of first curve */
#define TRSHRC  17304 /* keep region to right of first curve */
#define TRSHIL  17305 /* keep region inside closed loop */
#define TRSHOL  17306 /* keep region outside closed loop */
#define FXFT00  17400 /* blefxf option <base> */
#define FXFTNT  17401 /* do not trim blend */
#define FXFTTB  17402 /* trim blend to walls */
#define FXFTTW  17403 /* trim blend and walls */
#define FXFTAT  17404 /* trim blend and walls and attach blend */
#define FXFTCB  17405 /* constant radius rolling ball blend */
#define FXFTVB  17406 /* variable radius rolling ball blend */
#define FXFTHL  17407 /* blend constrained by tangent hold lines  */
#define FXFTCE  17408 /* blend constrained by cliffedges  */
#define FXFTHP  17409 /* help point provided for blend */
#define FXFTLP  17410 /* limit point provided for blend */
#define FXFTPR  17411 /* blend may propagate outside walls */
#define FXFTMS  17412 /* create multiple blends if possible */
#define FXFTTL  17413 /* tolerance associated with blend */
#define FXFTRC  17414 /* get rho values from law curve */
#define FXFTEO  17415 /* allow notching */
#define FXFTCL  17416 /* blend constrained by conic hold lines */
#define FXFTSO  17417 /* create solid body if possible */
#define FXFTCC  17418 /* blend curvature continuous at hold lines */
#define FXFTDB  17419 /* disc blend */
#define FXFTST  17420 /* short trim blend to walls */
#define FXFTLT  17421 /* long trim blend to walls */
#define FXFE00  17450 /* blefxf error <base> */
#define FXFEOK  17451 /* face face blend succeeded */
#define FXFEST  17452 /* failed to attach blend */
#define FXFEER  17453 /* failed to create blend */
#define FXFEID  17454 /* insufficient data to create blend */
#define FXFEXD  17455 /* inconsistent blend data */
#define FXFEIF  17456 /* invalid side wall */
#define FXFEIR  17457 /* invalid blend radius definition */
#define FXFEIH  17458 /* invalid tangent hold line data */
#define FXFEIC  17459 /* invalid cliffedge data */
#define FXFEFC  17460 /* face too tightly curved */
#define FXFERS  17461 /* blend radius is too small */
#define FXFERL  17462 /* blend radius is too large */
#define FXFELN  17463 /* left wall normal is wrong */
#define FXFERN  17464 /* right wall normal is wrong */
#define FXFEBN  17465 /* both wall normals are wrong */
#define FXFESC  17466 /* blend sheets intersect */
#define FXFEWC  17467 /* walls clash */
#define FXFEGX  17468 /* blend face has self-intersecting geometry */
#define FXFEFF  17469 /* blend has resulted in face-face inconsistency */
#define FXFERV  17470 /* invalid rho values in law curve */
#define FXFEAR  17471 /* ranges too asymmetric for geometry */
#define FXFECL  17472 /* invalid conic hold line data */
#define FXFEIS  17473 /* invalid spine data */

#endif /* PARASOLID_TOKENS_H_INCLUDED */

