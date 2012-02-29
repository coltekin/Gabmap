
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "strutils.h"
#include "dist_matrix.h"

#define MAX_IDX 2048
static const int didx[] = {
0x000000,0x000001,0x000003,0x000006,0x00000a,0x00000f,0x000015,0x00001c,
0x000024,0x00002d,0x000037,0x000042,0x00004e,0x00005b,0x000069,0x000078,
0x000088,0x000099,0x0000ab,0x0000be,0x0000d2,0x0000e7,0x0000fd,0x000114,
0x00012c,0x000145,0x00015f,0x00017a,0x000196,0x0001b3,0x0001d1,0x0001f0,
0x000210,0x000231,0x000253,0x000276,0x00029a,0x0002bf,0x0002e5,0x00030c,
0x000334,0x00035d,0x000387,0x0003b2,0x0003de,0x00040b,0x000439,0x000468,
0x000498,0x0004c9,0x0004fb,0x00052e,0x000562,0x000597,0x0005cd,0x000604,
0x00063c,0x000675,0x0006af,0x0006ea,0x000726,0x000763,0x0007a1,0x0007e0,
0x000820,0x000861,0x0008a3,0x0008e6,0x00092a,0x00096f,0x0009b5,0x0009fc,
0x000a44,0x000a8d,0x000ad7,0x000b22,0x000b6e,0x000bbb,0x000c09,0x000c58,
0x000ca8,0x000cf9,0x000d4b,0x000d9e,0x000df2,0x000e47,0x000e9d,0x000ef4,
0x000f4c,0x000fa5,0x000fff,0x00105a,0x0010b6,0x001113,0x001171,0x0011d0,
0x001230,0x001291,0x0012f3,0x001356,0x0013ba,0x00141f,0x001485,0x0014ec,
0x001554,0x0015bd,0x001627,0x001692,0x0016fe,0x00176b,0x0017d9,0x001848,
0x0018b8,0x001929,0x00199b,0x001a0e,0x001a82,0x001af7,0x001b6d,0x001be4,
0x001c5c,0x001cd5,0x001d4f,0x001dca,0x001e46,0x001ec3,0x001f41,0x001fc0,
0x002040,0x0020c1,0x002143,0x0021c6,0x00224a,0x0022cf,0x002355,0x0023dc,
0x002464,0x0024ed,0x002577,0x002602,0x00268e,0x00271b,0x0027a9,0x002838,
0x0028c8,0x002959,0x0029eb,0x002a7e,0x002b12,0x002ba7,0x002c3d,0x002cd4,
0x002d6c,0x002e05,0x002e9f,0x002f3a,0x002fd6,0x003073,0x003111,0x0031b0,
0x003250,0x0032f1,0x003393,0x003436,0x0034da,0x00357f,0x003625,0x0036cc,
0x003774,0x00381d,0x0038c7,0x003972,0x003a1e,0x003acb,0x003b79,0x003c28,
0x003cd8,0x003d89,0x003e3b,0x003eee,0x003fa2,0x004057,0x00410d,0x0041c4,
0x00427c,0x004335,0x0043ef,0x0044aa,0x004566,0x004623,0x0046e1,0x0047a0,
0x004860,0x004921,0x0049e3,0x004aa6,0x004b6a,0x004c2f,0x004cf5,0x004dbc,
0x004e84,0x004f4d,0x005017,0x0050e2,0x0051ae,0x00527b,0x005349,0x005418,
0x0054e8,0x0055b9,0x00568b,0x00575e,0x005832,0x005907,0x0059dd,0x005ab4,
0x005b8c,0x005c65,0x005d3f,0x005e1a,0x005ef6,0x005fd3,0x0060b1,0x006190,
0x006270,0x006351,0x006433,0x006516,0x0065fa,0x0066df,0x0067c5,0x0068ac,
0x006994,0x006a7d,0x006b67,0x006c52,0x006d3e,0x006e2b,0x006f19,0x007008,
0x0070f8,0x0071e9,0x0072db,0x0073ce,0x0074c2,0x0075b7,0x0076ad,0x0077a4,
0x00789c,0x007995,0x007a8f,0x007b8a,0x007c86,0x007d83,0x007e81,0x007f80,
0x008080,0x008181,0x008283,0x008386,0x00848a,0x00858f,0x008695,0x00879c,
0x0088a4,0x0089ad,0x008ab7,0x008bc2,0x008cce,0x008ddb,0x008ee9,0x008ff8,
0x009108,0x009219,0x00932b,0x00943e,0x009552,0x009667,0x00977d,0x009894,
0x0099ac,0x009ac5,0x009bdf,0x009cfa,0x009e16,0x009f33,0x00a051,0x00a170,
0x00a290,0x00a3b1,0x00a4d3,0x00a5f6,0x00a71a,0x00a83f,0x00a965,0x00aa8c,
0x00abb4,0x00acdd,0x00ae07,0x00af32,0x00b05e,0x00b18b,0x00b2b9,0x00b3e8,
0x00b518,0x00b649,0x00b77b,0x00b8ae,0x00b9e2,0x00bb17,0x00bc4d,0x00bd84,
0x00bebc,0x00bff5,0x00c12f,0x00c26a,0x00c3a6,0x00c4e3,0x00c621,0x00c760,
0x00c8a0,0x00c9e1,0x00cb23,0x00cc66,0x00cdaa,0x00ceef,0x00d035,0x00d17c,
0x00d2c4,0x00d40d,0x00d557,0x00d6a2,0x00d7ee,0x00d93b,0x00da89,0x00dbd8,
0x00dd28,0x00de79,0x00dfcb,0x00e11e,0x00e272,0x00e3c7,0x00e51d,0x00e674,
0x00e7cc,0x00e925,0x00ea7f,0x00ebda,0x00ed36,0x00ee93,0x00eff1,0x00f150,
0x00f2b0,0x00f411,0x00f573,0x00f6d6,0x00f83a,0x00f99f,0x00fb05,0x00fc6c,
0x00fdd4,0x00ff3d,0x0100a7,0x010212,0x01037e,0x0104eb,0x010659,0x0107c8,
0x010938,0x010aa9,0x010c1b,0x010d8e,0x010f02,0x011077,0x0111ed,0x011364,
0x0114dc,0x011655,0x0117cf,0x01194a,0x011ac6,0x011c43,0x011dc1,0x011f40,
0x0120c0,0x012241,0x0123c3,0x012546,0x0126ca,0x01284f,0x0129d5,0x012b5c,
0x012ce4,0x012e6d,0x012ff7,0x013182,0x01330e,0x01349b,0x013629,0x0137b8,
0x013948,0x013ad9,0x013c6b,0x013dfe,0x013f92,0x014127,0x0142bd,0x014454,
0x0145ec,0x014785,0x01491f,0x014aba,0x014c56,0x014df3,0x014f91,0x015130,
0x0152d0,0x015471,0x015613,0x0157b6,0x01595a,0x015aff,0x015ca5,0x015e4c,
0x015ff4,0x01619d,0x016347,0x0164f2,0x01669e,0x01684b,0x0169f9,0x016ba8,
0x016d58,0x016f09,0x0170bb,0x01726e,0x017422,0x0175d7,0x01778d,0x017944,
0x017afc,0x017cb5,0x017e6f,0x01802a,0x0181e6,0x0183a3,0x018561,0x018720,
0x0188e0,0x018aa1,0x018c63,0x018e26,0x018fea,0x0191af,0x019375,0x01953c,
0x019704,0x0198cd,0x019a97,0x019c62,0x019e2e,0x019ffb,0x01a1c9,0x01a398,
0x01a568,0x01a739,0x01a90b,0x01aade,0x01acb2,0x01ae87,0x01b05d,0x01b234,
0x01b40c,0x01b5e5,0x01b7bf,0x01b99a,0x01bb76,0x01bd53,0x01bf31,0x01c110,
0x01c2f0,0x01c4d1,0x01c6b3,0x01c896,0x01ca7a,0x01cc5f,0x01ce45,0x01d02c,
0x01d214,0x01d3fd,0x01d5e7,0x01d7d2,0x01d9be,0x01dbab,0x01dd99,0x01df88,
0x01e178,0x01e369,0x01e55b,0x01e74e,0x01e942,0x01eb37,0x01ed2d,0x01ef24,
0x01f11c,0x01f315,0x01f50f,0x01f70a,0x01f906,0x01fb03,0x01fd01,0x01ff00,
0x020100,0x020301,0x020503,0x020706,0x02090a,0x020b0f,0x020d15,0x020f1c,
0x021124,0x02132d,0x021537,0x021742,0x02194e,0x021b5b,0x021d69,0x021f78,
0x022188,0x022399,0x0225ab,0x0227be,0x0229d2,0x022be7,0x022dfd,0x023014,
0x02322c,0x023445,0x02365f,0x02387a,0x023a96,0x023cb3,0x023ed1,0x0240f0,
0x024310,0x024531,0x024753,0x024976,0x024b9a,0x024dbf,0x024fe5,0x02520c,
0x025434,0x02565d,0x025887,0x025ab2,0x025cde,0x025f0b,0x026139,0x026368,
0x026598,0x0267c9,0x0269fb,0x026c2e,0x026e62,0x027097,0x0272cd,0x027504,
0x02773c,0x027975,0x027baf,0x027dea,0x028026,0x028263,0x0284a1,0x0286e0,
0x028920,0x028b61,0x028da3,0x028fe6,0x02922a,0x02946f,0x0296b5,0x0298fc,
0x029b44,0x029d8d,0x029fd7,0x02a222,0x02a46e,0x02a6bb,0x02a909,0x02ab58,
0x02ada8,0x02aff9,0x02b24b,0x02b49e,0x02b6f2,0x02b947,0x02bb9d,0x02bdf4,
0x02c04c,0x02c2a5,0x02c4ff,0x02c75a,0x02c9b6,0x02cc13,0x02ce71,0x02d0d0,
0x02d330,0x02d591,0x02d7f3,0x02da56,0x02dcba,0x02df1f,0x02e185,0x02e3ec,
0x02e654,0x02e8bd,0x02eb27,0x02ed92,0x02effe,0x02f26b,0x02f4d9,0x02f748,
0x02f9b8,0x02fc29,0x02fe9b,0x03010e,0x030382,0x0305f7,0x03086d,0x030ae4,
0x030d5c,0x030fd5,0x03124f,0x0314ca,0x031746,0x0319c3,0x031c41,0x031ec0,
0x032140,0x0323c1,0x032643,0x0328c6,0x032b4a,0x032dcf,0x033055,0x0332dc,
0x033564,0x0337ed,0x033a77,0x033d02,0x033f8e,0x03421b,0x0344a9,0x034738,
0x0349c8,0x034c59,0x034eeb,0x03517e,0x035412,0x0356a7,0x03593d,0x035bd4,
0x035e6c,0x036105,0x03639f,0x03663a,0x0368d6,0x036b73,0x036e11,0x0370b0,
0x037350,0x0375f1,0x037893,0x037b36,0x037dda,0x03807f,0x038325,0x0385cc,
0x038874,0x038b1d,0x038dc7,0x039072,0x03931e,0x0395cb,0x039879,0x039b28,
0x039dd8,0x03a089,0x03a33b,0x03a5ee,0x03a8a2,0x03ab57,0x03ae0d,0x03b0c4,
0x03b37c,0x03b635,0x03b8ef,0x03bbaa,0x03be66,0x03c123,0x03c3e1,0x03c6a0,
0x03c960,0x03cc21,0x03cee3,0x03d1a6,0x03d46a,0x03d72f,0x03d9f5,0x03dcbc,
0x03df84,0x03e24d,0x03e517,0x03e7e2,0x03eaae,0x03ed7b,0x03f049,0x03f318,
0x03f5e8,0x03f8b9,0x03fb8b,0x03fe5e,0x040132,0x040407,0x0406dd,0x0409b4,
0x040c8c,0x040f65,0x04123f,0x04151a,0x0417f6,0x041ad3,0x041db1,0x042090,
0x042370,0x042651,0x042933,0x042c16,0x042efa,0x0431df,0x0434c5,0x0437ac,
0x043a94,0x043d7d,0x044067,0x044352,0x04463e,0x04492b,0x044c19,0x044f08,
0x0451f8,0x0454e9,0x0457db,0x045ace,0x045dc2,0x0460b7,0x0463ad,0x0466a4,
0x04699c,0x046c95,0x046f8f,0x04728a,0x047586,0x047883,0x047b81,0x047e80,
0x048180,0x048481,0x048783,0x048a86,0x048d8a,0x04908f,0x049395,0x04969c,
0x0499a4,0x049cad,0x049fb7,0x04a2c2,0x04a5ce,0x04a8db,0x04abe9,0x04aef8,
0x04b208,0x04b519,0x04b82b,0x04bb3e,0x04be52,0x04c167,0x04c47d,0x04c794,
0x04caac,0x04cdc5,0x04d0df,0x04d3fa,0x04d716,0x04da33,0x04dd51,0x04e070,
0x04e390,0x04e6b1,0x04e9d3,0x04ecf6,0x04f01a,0x04f33f,0x04f665,0x04f98c,
0x04fcb4,0x04ffdd,0x050307,0x050632,0x05095e,0x050c8b,0x050fb9,0x0512e8,
0x051618,0x051949,0x051c7b,0x051fae,0x0522e2,0x052617,0x05294d,0x052c84,
0x052fbc,0x0532f5,0x05362f,0x05396a,0x053ca6,0x053fe3,0x054321,0x054660,
0x0549a0,0x054ce1,0x055023,0x055366,0x0556aa,0x0559ef,0x055d35,0x05607c,
0x0563c4,0x05670d,0x056a57,0x056da2,0x0570ee,0x05743b,0x057789,0x057ad8,
0x057e28,0x058179,0x0584cb,0x05881e,0x058b72,0x058ec7,0x05921d,0x059574,
0x0598cc,0x059c25,0x059f7f,0x05a2da,0x05a636,0x05a993,0x05acf1,0x05b050,
0x05b3b0,0x05b711,0x05ba73,0x05bdd6,0x05c13a,0x05c49f,0x05c805,0x05cb6c,
0x05ced4,0x05d23d,0x05d5a7,0x05d912,0x05dc7e,0x05dfeb,0x05e359,0x05e6c8,
0x05ea38,0x05eda9,0x05f11b,0x05f48e,0x05f802,0x05fb77,0x05feed,0x060264,
0x0605dc,0x060955,0x060ccf,0x06104a,0x0613c6,0x061743,0x061ac1,0x061e40,
0x0621c0,0x062541,0x0628c3,0x062c46,0x062fca,0x06334f,0x0636d5,0x063a5c,
0x063de4,0x06416d,0x0644f7,0x064882,0x064c0e,0x064f9b,0x065329,0x0656b8,
0x065a48,0x065dd9,0x06616b,0x0664fe,0x066892,0x066c27,0x066fbd,0x067354,
0x0676ec,0x067a85,0x067e1f,0x0681ba,0x068556,0x0688f3,0x068c91,0x069030,
0x0693d0,0x069771,0x069b13,0x069eb6,0x06a25a,0x06a5ff,0x06a9a5,0x06ad4c,
0x06b0f4,0x06b49d,0x06b847,0x06bbf2,0x06bf9e,0x06c34b,0x06c6f9,0x06caa8,
0x06ce58,0x06d209,0x06d5bb,0x06d96e,0x06dd22,0x06e0d7,0x06e48d,0x06e844,
0x06ebfc,0x06efb5,0x06f36f,0x06f72a,0x06fae6,0x06fea3,0x070261,0x070620,
0x0709e0,0x070da1,0x071163,0x071526,0x0718ea,0x071caf,0x072075,0x07243c,
0x072804,0x072bcd,0x072f97,0x073362,0x07372e,0x073afb,0x073ec9,0x074298,
0x074668,0x074a39,0x074e0b,0x0751de,0x0755b2,0x075987,0x075d5d,0x076134,
0x07650c,0x0768e5,0x076cbf,0x07709a,0x077476,0x077853,0x077c31,0x078010,
0x0783f0,0x0787d1,0x078bb3,0x078f96,0x07937a,0x07975f,0x079b45,0x079f2c,
0x07a314,0x07a6fd,0x07aae7,0x07aed2,0x07b2be,0x07b6ab,0x07ba99,0x07be88,
0x07c278,0x07c669,0x07ca5b,0x07ce4e,0x07d242,0x07d637,0x07da2d,0x07de24,
0x07e21c,0x07e615,0x07ea0f,0x07ee0a,0x07f206,0x07f603,0x07fa01
};


void dist_matrix_free(struct dist_matrix *d)
{
    int i;

    for (i = 0; i < d->n; i++) {
        free(d->labels[i]);
    }
    free(d->labels);
    free(d->diff);
    free(d);
}

struct dist_matrix *read_dist_matrix(char *fname)
{
    struct dist_matrix *d;
    FILE *fp = fopen(fname, "r");
    char    buf[1024]; // TODO: make this dynamic

    if (!fp) {
        fprintf(stderr, "Cannot open file `%s'.\n", fname);
        exit(1);
    }
    
    d = malloc(sizeof *d);

    fgets(buf, 1024, fp);
    while (!feof(fp)) {
        if (buf[0] != '#' && buf[0] != '\n') {
            d->n = atoi(str_strip(buf, " \t\n\r"));
            break;
        }
        fgets(buf, 1024, fp);
    }

    d->labels = malloc((d->n + 1) * sizeof (*d->labels));
    d->diff = malloc((d->n*(d->n -1) /2) * sizeof (*d->diff));

    int i = 0;
    fgets(buf, 1024, fp);
    while (i < d->n) {
        assert(!feof(fp));
        if (buf[0] != '#' && buf[0] != '\n') {
            d->labels[i] = strdup(str_strip(buf, " \t\n\r"));
            i++;
        }
        fgets(buf, 1024, fp);
    }

    i = 0;
    while (i < ((d->n * (d->n -1)) / 2)) {
        assert(!feof(fp));
        if (buf[0] != '#' && buf[0] != '\n') {
            if (!strncmp("NA", buf, 2)) {
                d->diff[i] = NAN;
            } else {
                d->diff[i] = atof(str_strip(buf, " \t\n\r"));
            }
            i++;
        }
        fgets(buf, 1024, fp);
    }

    fclose(fp);
    return d;
}


double get_distance(struct dist_matrix *d, int i, int j)
{
    assert(i < d->n && j < d->n);
    if (i == j) return 0.0;
    if (i < j) {
        int k;
        k = i; i = j; j = k;
    }
    int idx;
    if (i < MAX_IDX) { // use precomputed table
        idx = didx[i-1] + j;
    } else {
        idx = 0;
        int k;
        for (k = 1; k < i; k++) {
            idx += k - 1;
        }
        idx += j;
    }
    return d->diff[idx];
}


