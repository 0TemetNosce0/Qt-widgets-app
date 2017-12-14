// iatdemo_with_multi-result.c : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "stdio.h"
#include <windows.h>
#include <conio.h>
#include <errno.h>

#include "../../include/qisr.h"
#include "../../include/msp_cmn.h"
#include "../../include/msp_errors.h"


#ifdef _WIN64
#pragma comment(lib,"../../lib/msc_x64.lib")//x64
#else
#pragma comment(lib,"../../lib/msc.lib")//x86
#endif

#define  BUFFER_NUM 1024 * 4
#define  AMR_HEAD_SIZE  6

void run_iat(const char* src_wav_filename ,const char* des_text_filename ,  const char* param)
{
	char rec_result[1024*4] = {0};
	const char *sessionID = NULL;
	FILE *f_pcm = NULL;
	FILE* fout = NULL;
	char *pPCM = NULL;
	int lastAudio = 0 ;
	int audStat = MSP_AUDIO_SAMPLE_CONTINUE ;
	int epStatus = MSP_EP_LOOKING_FOR_SPEECH;
	int recStatus = MSP_REC_STATUS_SUCCESS ;
	long pcmCount = 0;
	long pcmSize = 0;
	int errCode = 10 ;

	sessionID = QISRSessionBegin(NULL, param, &errCode);//��ʼһ·�Ự
	fout = fopen( des_text_filename , "ab");
	f_pcm = fopen(src_wav_filename, "rb");
	if (NULL != f_pcm) {
		fseek(f_pcm, 0, SEEK_END);
		pcmSize = ftell(f_pcm);
		fseek(f_pcm, 0, SEEK_SET);
		pPCM = (char *)malloc(pcmSize);
		fread((void *)pPCM, pcmSize, 1, f_pcm);
		fclose(f_pcm);
		f_pcm = NULL;
	}
	while (1) {
		unsigned int len = 6400;
		int ret = 0;
		if (pcmSize < 12800) {
			len = pcmSize;
			lastAudio = 1;//��Ƶ����С��12800
		}
		audStat = MSP_AUDIO_SAMPLE_CONTINUE;//�к����Ƶ
		if (pcmCount == 0)
			audStat = MSP_AUDIO_SAMPLE_FIRST;
		if (len<=0)
		{
			break;
		}
		printf("csid=%s,count=%d,aus=%d,",sessionID,pcmCount/len,audStat);
		ret = QISRAudioWrite(sessionID, (const void *)&pPCM[pcmCount], len, audStat, &epStatus, &recStatus);
		printf("eps=%d,rss=%d,ret=%d\n",epStatus,recStatus,errCode);
		if (ret != 0)
			break;
		pcmCount += (long)len;
		pcmSize -= (long)len;
		if (recStatus == MSP_REC_STATUS_SUCCESS) {
			const char *rslt = QISRGetResult(sessionID, &recStatus, 0, &errCode);//������Ѿ���ʶ���������Ի�ȡ
			if (NULL != rslt)
				strcat(rec_result,rslt);
		}
		if (epStatus == MSP_EP_AFTER_SPEECH)
			break;
		_sleep(150);//ģ����˵��ʱ���϶
	}
	QISRAudioWrite(sessionID, (const void *)NULL, 0, MSP_AUDIO_SAMPLE_LAST, &epStatus, &recStatus);
	free(pPCM);
	pPCM = NULL;
	while (recStatus != MSP_REC_STATUS_COMPLETE && 0 == errCode) {
		const char *rslt = QISRGetResult(sessionID, &recStatus, 0, &errCode);//��ȡ���
		if (NULL != rslt)
		{
			strcat(rec_result,rslt);
			fwrite(rslt, 1, strlen(rslt), fout);
			
		}
		_sleep(150);
	}
	fclose(fout);
	QISRSessionEnd(sessionID, NULL);
	printf("=============================================================\n");
	printf("The result is: %s\n",rec_result);
	printf("=============================================================\n");
}

int main(int argc, char* argv[])
{
	///APPID��������Ķ�
	const char* login_config = "appid = 53d11199, work_dir =   .  ";
	const char* param1 = "sub=iat,auf=audio/L16;rate=16000,aue=speex-wb,ent=sms16k,nbest=5";//���5����ѡ���ʽֻ��Ϊjson������ֻ��Ϊutf8
	const char* param2 = "sub=iat,auf=audio/L16;rate=16000,aue=speex-wb,ent=sms16k,nbest=1";//���2����ѡ���ʽֻ��Ϊjson������ֻ��Ϊutf8,nbest��ȡֵ��ΧΪ1~5
	const char* output_file = "iat_result.txt";
	int ret = 0;
	char key = 0;

	//�û���¼
	ret = MSPLogin(NULL, NULL, login_config);//��һ������Ϊ�û������ڶ�������Ϊ���룬�����������ǵ�¼�������û�����������Ҫ��http://open.voicecloud.cnע�Ტ��ȡappid
	if ( ret != MSP_SUCCESS )
	{
		printf("MSPLogin failed , Error code %d.\n",ret);
		goto exit;
	}
	//��ʼһ·תд�Ự
	run_iat("wav/iflytek04.wav" , output_file ,  param1);                      //iflytek04��Ӧ����Ƶ����"һ�����������߰˾�ʮ"
	run_iat("wav/iflytek04.wav" , output_file ,  param2);                      //iflytek04��Ӧ����Ƶ����"һ�����������߰˾�ʮ"

	exit:
	MSPLogout();//�˳���¼
	key = _getch();
	return 0;
}

