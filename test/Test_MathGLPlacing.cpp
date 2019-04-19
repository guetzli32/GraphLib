#include <iostream>
#include <graphlib/gl>
#include <mgl2/mgl.h>

template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void plotData(gl::Graph<SCALAR, STORAGE_KIND, DIRECTION> g, mglGraph *gr)
{
    using GRAPH = gl::Graph<SCALAR, STORAGE_KIND, DIRECTION>;
    double radius = 100;

    gr->SetRange('x', -radius, radius);
    gr->SetRange('y', -radius, radius);

    typename GRAPH::idx_t numNodes = g.numNodes();
    double degreePerNode = 2 * M_PI / (1.0 * numNodes);

    std::vector<std::pair<double, double>> positions(numNodes);

    for (typename GRAPH::idx_t i = 0; i < numNodes; i++)
    {
        positions[i] = std::pair<double, double>(radius * std::cos(i * degreePerNode), radius * std::sin(i * degreePerNode));
    }

    std::string output_args;
    for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
    {
        output_args = "{x" + it->color().RGB() + "}-";
        mglPoint p1(positions[it->source()].first, positions[it->source()].second);
        mglPoint p2(positions[it->dest()].first, positions[it->dest()].second);
        gr->Line(p1, p2, output_args.data());
    }
}

int main(int argc, char const *argv[])
{
    //gl::Graph<int, gl::Matrix, gl::Directed> g(10); // gl::GraphMiu
    gl::graphMiu g(100);
    g.setEdge(89, 97, 1, gl::Color(0.5680268140472136, 0.7097487536559117, 0.691474082905443));
    g.setEdge(74, 12, 1, gl::Color(0.5734269126810962, 0.28493681251199954, 0.09825670614211257));
    g.setEdge(72, 73, 1, gl::Color(0.5310947245107265, 0.7836254822813067, 0.3840882729176651));
    g.setEdge(65, 61, 1, gl::Color(0.9716100628590986, 0.9685028977078565, 0.19702499082125224));
    g.setEdge(53, 58, 1, gl::Color(0.5328880927296333, 0.5331199866608994, 0.8686888825633304));
    g.setEdge(65, 89, 1, gl::Color(0.36024689842563673, 0.27893266217767654, 0.8034818473082206));
    g.setEdge(2, 62, 1, gl::Color(0.7165187566240653, 0.28993399677441944, 0.963738705839617));
    g.setEdge(66, 41, 1, gl::Color(0.4254924600479254, 0.05717326420473623, 0.2990786481092702));
    g.setEdge(26, 92, 1, gl::Color(0.4661201337732418, 0.5171802976132938, 0.753617196788753));
    g.setEdge(65, 19, 1, gl::Color(0.2683190785681946, 0.8988177862979965, 0.8396398687835576));
    g.setEdge(73, 82, 1, gl::Color(0.29962031491666363, 0.8668809030188633, 0.1991298982898113));
    g.setEdge(16, 31, 1, gl::Color(0.520468074494538, 0.2932268722002359, 0.30661658109277634));
    g.setEdge(42, 96, 1, gl::Color(0.3655745736112621, 0.4515816695762178, 0.5755913048743164));
    g.setEdge(6, 44, 1, gl::Color(0.5424278131582732, 0.2861266222848564, 0.1544524022849728));
    g.setEdge(64, 39, 1, gl::Color(0.536853148506159, 0.8526478888247095, 0.7019524850963386));
    g.setEdge(35, 49, 1, gl::Color(0.9134854411430855, 0.5601978389280521, 0.9158193298255506));
    g.setEdge(43, 57, 1, gl::Color(0.8036251302464164, 0.4208037149262236, 0.4463697323000507));
    g.setEdge(65, 12, 1, gl::Color(0.29869420009316294, 0.9288473396050604, 0.5037354773199767));
    g.setEdge(9, 14, 1, gl::Color(0.1376223566121355, 0.1302586696351532, 0.4372113522272181));
    g.setEdge(60, 86, 1, gl::Color(0.15993120409701544, 0.2901923222517391, 0.45472846747255935));
    g.setEdge(9, 20, 1, gl::Color(0.7149071174037368, 0.45666484036332233, 0.22754512294848006));
    g.setEdge(69, 70, 1, gl::Color(0.5164196478640609, 0.5208781938294781, 0.6050533677972418));
    g.setEdge(29, 79, 1, gl::Color(0.2654573501263683, 0.9234500997058263, 0.8557484916336138));
    g.setEdge(19, 40, 1, gl::Color(0.16499266060768414, 0.9893369813609194, 0.416471590658435));
    g.setEdge(15, 83, 1, gl::Color(0.1622395631761766, 0.9410044170996806, 0.8357136052069265));
    g.setEdge(13, 20, 1, gl::Color(0.2956621678137529, 0.7763263988538968, 0.20803167206838613));
    g.setEdge(81, 83, 1, gl::Color(0.33487920924602566, 0.645471680008411, 0.0898327619846978));
    g.setEdge(56, 46, 1, gl::Color(0.7936717534609308, 0.1673328915966008, 0.5648376793485693));
    g.setEdge(39, 10, 1, gl::Color(0.5745951968479932, 0.485083255014106, 0.26762705784992447));
    g.setEdge(71, 94, 1, gl::Color(0.2250699063149041, 0.3678681055827743, 0.07209378199748206));
    g.setEdge(98, 41, 1, gl::Color(0.3503277132076341, 0.12649747901994202, 0.3794976315864309));
    g.setEdge(79, 97, 1, gl::Color(0.635926761190148, 0.7393933862492706, 0.5623685951488095));
    g.setEdge(6, 40, 1, gl::Color(0.697032527501289, 0.7201369990741332, 0.9763720223042871));
    g.setEdge(62, 13, 1, gl::Color(0.39165691041158635, 0.11585568286416503, 0.48737020152219046));
    g.setEdge(47, 74, 1, gl::Color(0.9780116140238313, 0.7891993440210066, 0.9094208126832622));
    g.setEdge(28, 9, 1, gl::Color(0.25105644040241615, 0.7151679866310957, 0.25561254182857207));
    g.setEdge(56, 29, 1, gl::Color(0.8254052892158443, 0.1734521323993734, 0.7522206924266449));
    g.setEdge(86, 81, 1, gl::Color(0.7882591552853968, 0.7270755691321853, 0.8063556465554187));
    g.setEdge(24, 97, 1, gl::Color(0.8807863473389728, 0.31765486874647897, 0.898704993173096));
    g.setEdge(70, 22, 1, gl::Color(0.6882320023877151, 0.701293967970462, 0.2513566787334056));
    g.setEdge(32, 7, 1, gl::Color(0.15225534177429945, 0.679959102078458, 0.6263755928403204));
    g.setEdge(61, 26, 1, gl::Color(0.5629104276203296, 0.9620608819054087, 0.07382557552550872));
    g.setEdge(9, 21, 1, gl::Color(0.42431402473937585, 0.6512193337097676, 0.8467768272448776));
    g.setEdge(19, 56, 1, gl::Color(0.7776050015749615, 0.46040737125927733, 0.3060889354808013));
    g.setEdge(74, 68, 1, gl::Color(0.7167596179883263, 0.11014682356169947, 0.3289060378571177));
    g.setEdge(56, 4, 1, gl::Color(0.1898995650149521, 0.6678165947336026, 0.9079440351515246));
    g.setEdge(29, 88, 1, gl::Color(0.12012650671342606, 0.12289938390211841, 0.7298252876782287));
    g.setEdge(25, 59, 1, gl::Color(0.15548627135358573, 0.6387443788518898, 0.3023405397313591));
    g.setEdge(30, 26, 1, gl::Color(0.5094778036744924, 0.6083568951818182, 0.5884742444230031));
    g.setEdge(94, 95, 1, gl::Color(0.9035309556062865, 0.8847333016944611, 0.8497420161568926));
    g.setEdge(3, 65, 1, gl::Color(0.7464577960782566, 0.6728212493237934, 0.6405986204823357));
    g.setEdge(43, 81, 1, gl::Color(0.3492089909251179, 0.6195816914436305, 0.14368258298650116));
    g.setEdge(16, 47, 1, gl::Color(0.9274390883041551, 0.07019915137894428, 0.8760827044808088));
    g.setEdge(8, 50, 1, gl::Color(0.60671850016608, 0.2657809130005693, 0.1742879945027378));
    g.setEdge(27, 35, 1, gl::Color(0.3097354874218453, 0.3417181015633537, 0.5927503207467602));
    g.setEdge(50, 12, 1, gl::Color(0.828914252859762, 0.7016690429832086, 0.5556272111016118));
    g.setEdge(25, 58, 1, gl::Color(0.7268400141427517, 0.6556996868214134, 0.447289805148528));
    g.setEdge(39, 32, 1, gl::Color(0.1989143358511417, 0.038345581020354236, 0.13148324071141848));
    g.setEdge(49, 24, 1, gl::Color(0.6898337968310778, 0.9791422000690099, 0.9243397945350098));
    g.setEdge(28, 26, 1, gl::Color(0.3757370568883509, 0.26811434539782664, 0.7127217744789861));
    g.setEdge(11, 50, 1, gl::Color(0.3533592063905576, 0.7585939823812091, 0.3564649942943794));
    g.setEdge(60, 99, 1, gl::Color(0.228628148343898, 0.09843250430353345, 0.8915077278417594));
    g.setEdge(91, 95, 1, gl::Color(0.38218755096238455, 0.40066432287824627, 0.367651908093116));
    g.setEdge(38, 95, 1, gl::Color(0.21854790648805944, 0.5625890950775027, 0.9261784002865805));
    g.setEdge(22, 65, 1, gl::Color(0.739875960706411, 0.9071154416451299, 0.8242373048106333));
    g.setEdge(27, 45, 1, gl::Color(0.663301127953112, 0.33656483263386416, 0.5647092664437032));
    g.setEdge(99, 86, 1, gl::Color(0.5890784601903599, 0.5680497057368525, 0.7537556999715378));
    g.setEdge(44, 45, 1, gl::Color(0.22044819632591406, 0.7002920503523853, 0.5149781900735101));
    g.setEdge(7, 72, 1, gl::Color(0.5727783779006234, 0.5153961942039581, 0.4486696974311195));
    g.setEdge(2, 45, 1, gl::Color(0.9327488005665094, 0.42156604493535343, 0.2888057648927559));
    g.setEdge(9, 81, 1, gl::Color(0.2944459449120942, 0.2875212940901656, 0.997614511740156));
    g.setEdge(92, 64, 1, gl::Color(0.7950436229916779, 0.9679155397640129, 0.12882427737431923));
    g.setEdge(86, 89, 1, gl::Color(0.4659689224724455, 0.2410514837629305, 0.3130320753914593));
    g.setEdge(87, 7, 1, gl::Color(0.062028782961955464, 0.7121927271340431, 0.8207831690039187));
    g.setEdge(63, 10, 1, gl::Color(0.7801428679628506, 0.5653101531456045, 0.6653790753016835));
    g.setEdge(16, 2, 1, gl::Color(0.25272222414639545, 0.2753390460389127, 0.9535129477614329));
    g.setEdge(92, 67, 1, gl::Color(0.2861355014782492, 0.3004621923222581, 0.23163145032251575));
    g.setEdge(88, 76, 1, gl::Color(0.6482603817963102, 0.8659689413605316, 0.36318175484498527));
    g.setEdge(79, 21, 1, gl::Color(0.3407489344989464, 0.3355538470110391, 0.9904966156571368));
    g.setEdge(91, 47, 1, gl::Color(0.22879340472878118, 0.8934097127254315, 0.9691368135495997));
    g.setEdge(42, 15, 1, gl::Color(0.3551315625822826, 0.2502639233288645, 0.9128565673725849));
    g.setEdge(45, 57, 1, gl::Color(0.22052506535195016, 0.8368671656986386, 0.3251286985553653));
    g.setEdge(76, 89, 1, gl::Color(0.18066572831732597, 0.4763249455490929, 0.9454023196586794));
    g.setEdge(37, 53, 1, gl::Color(0.36376376463902516, 0.9434075364792681, 0.10837703956648426));
    g.setEdge(18, 72, 1, gl::Color(0.2762552590563624, 0.4259116076538012, 0.5661682001957732));
    g.setEdge(85, 20, 1, gl::Color(0.14853607712951655, 0.9209456760300262, 0.03942760029728909));
    g.setEdge(99, 59, 1, gl::Color(0.021399710463551047, 0.6765956487843889, 0.9930686655464136));
    g.setEdge(47, 57, 1, gl::Color(0.8054513787615474, 0.5286982886870285, 0.5854739149507688));
    g.setEdge(29, 81, 1, gl::Color(0.22041353037403932, 0.20033665250393995, 0.7001535539555237));
    g.setEdge(5, 64, 1, gl::Color(0.5403409073207602, 0.00833813917879811, 0.932123293328161));
    g.setEdge(36, 46, 1, gl::Color(0.9235233267705742, 0.6826273570343273, 0.8683482496637813));
    g.setEdge(91, 10, 1, gl::Color(0.200138681887839, 0.012734727855888361, 0.6468455708987522));
    g.setEdge(18, 40, 1, gl::Color(0.35160346939019727, 0.9024686363743554, 0.9003312469152095));
    g.setEdge(69, 10, 1, gl::Color(0.29737325794291813, 0.8747096727160467, 0.8037276713657174));
    g.setEdge(91, 65, 1, gl::Color(0.8232339684664088, 0.5826437884975462, 0.030139464288992945));
    g.setEdge(44, 26, 1, gl::Color(0.9937137549146301, 0.9220219201301425, 0.10388225441997956));
    g.setEdge(70, 77, 1, gl::Color(0.35658352219666956, 0.9197521449892825, 0.596265352648493));
    g.setEdge(14, 98, 1, gl::Color(0.5159447376577114, 0.8762264256064806, 0.25149950818516464));
    g.setEdge(37, 80, 1, gl::Color(0.6720963783701565, 0.5708661573239179, 0.9595052056358802));

    mglGraph gr;
    gr.SetSize(1000, 1000);

    plotData(g, &gr);

    gr.WritePNG("build/mathgl_placing.png");
    std::cout << "saved to build/mathgl_placing.png" << std::endl;

    return 0;
}
