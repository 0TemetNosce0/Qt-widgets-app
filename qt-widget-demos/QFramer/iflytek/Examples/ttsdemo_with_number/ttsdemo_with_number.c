// ttsdemo_with_number.c : Defines the entry point for the console application.
//
#include "stdlib.h"
#include "stdio.h"
#include <windows.h>
#include <conio.h>
#include <errno.h>

#include "../../include/qtts.h"
#include "../../include/msp_cmn.h"
#include "../../include/msp_errors.h"


#ifdef _WIN64
#pragma comment(lib,"../../lib/msc_x64.lib")//x64
#else
#pragma comment(lib,"../../lib/msc.lib")//x86
#endif

typedef int SR_DWORD;
typedef short int SR_WORD ;

//��Ƶͷ����ʽ
struct wave_pcm_hdr
{
	char            riff[4];                        // = "RIFF"
	SR_DWORD        size_8;                         // = FileSize - 8
	char            wave[4];                        // = "WAVE"
	char            fmt[4];                         // = "fmt "
	SR_DWORD        dwFmtSize;                      // = ��һ���ṹ��Ĵ�С : 16

	SR_WORD         format_tag;              // = PCM : 1
	SR_WORD         channels;                       // = ͨ���� : 1
	SR_DWORD        samples_per_sec;        // = ������ : 8000 | 6000 | 11025 | 16000
	SR_DWORD        avg_bytes_per_sec;      // = ÿ���ֽ��� : dwSamplesPerSec * wBitsPerSample / 8
	SR_WORD         block_align;            // = ÿ�������ֽ��� : wBitsPerSample / 8
	SR_WORD         bits_per_sample;         // = ����������: 8 | 16

	char            data[4];                        // = "data";
	SR_DWORD        data_size;                // = �����ݳ��� : FileSize - 44 
} ;

//Ĭ����Ƶͷ������
struct wave_pcm_hdr default_pcmwavhdr = 
{
	{ 'R', 'I', 'F', 'F' },
	0,
	{'W', 'A', 'V', 'E'},
	{'f', 'm', 't', ' '},
	16,
	1,
	1,
	16000,
	32000,
	2,
	16,
	{'d', 'a', 't', 'a'},
	0  
};

int text_to_speech(const char* src_text ,const char* des_path ,const char* params)
{
	struct wave_pcm_hdr pcmwavhdr = default_pcmwavhdr;
	const char* sess_id = NULL;
	int ret = -1;
	unsigned int text_len = 0;
	char* audio_data = NULL;
	unsigned int audio_len = 0;
	int synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;
	FILE* fp = NULL;

	printf("begin to synth...\n");
	if (NULL == src_text || NULL == des_path)
	{
		printf("params is null!\n");
		return ret;
	}
	text_len = (unsigned int)strlen(src_text);
	fp = fopen(des_path,"wb");
	if (NULL == fp)
	{
		printf("open file %s error\n",des_path);
		return ret;
	}
	sess_id = QTTSSessionBegin(params, &ret);
	if ( ret != MSP_SUCCESS )
	{
		printf("QTTSSessionBegin: qtts begin session failed Error code %d.\n",ret);
		return ret;
	}

	ret = QTTSTextPut(sess_id, src_text, text_len, NULL );
	if ( ret != MSP_SUCCESS )
	{
		printf("QTTSTextPut: qtts put text failed Error code %d.\n",ret);
		QTTSSessionEnd(sess_id, "TextPutError");
		return ret;
	}
	fwrite(&pcmwavhdr, sizeof(pcmwavhdr) ,1, fp);
	while (1) 
	{
		const void *data = QTTSAudioGet(sess_id, &audio_len, &synth_status, &ret);
		if (NULL != data)
		{
			fwrite(data, audio_len, 1, fp);
		    pcmwavhdr.data_size += audio_len;//����pcm���ݵĴ�С
		}
		if (synth_status == MSP_TTS_FLAG_DATA_END || ret != 0) 
			break;
	}

	//����pcm�ļ�ͷ���ݵĴ�С
	pcmwavhdr.size_8 += pcmwavhdr.data_size + 36;

	//��������������д���ļ�ͷ��
	fseek(fp, 4, 0);
	fwrite(&pcmwavhdr.size_8,sizeof(pcmwavhdr.size_8), 1, fp);
	fseek(fp, 40, 0);
	fwrite(&pcmwavhdr.data_size,sizeof(pcmwavhdr.data_size), 1, fp);
	fclose(fp);

	ret = QTTSSessionEnd(sess_id, NULL);
	if ( ret != MSP_SUCCESS )
	{
		printf("QTTSSessionEnd: qtts end failed Error code %d.\n",ret);
	}
	return ret;
}

int main(int argc, char* argv[])
{
	///APPID��������Ķ�
	const char* login_configs = "appid = 53d11199, work_dir =   .  ";//��¼����
	const char* text  = "10086";//���ϳɵ��ı�
	const char*  filename = "text_to_speech_withnumber_test.pcm";//�ϳɵ������ļ�
	const char* param = "bgs=1, spd = 50, vol = 50 , rdn = 2";//rdn = 1 �ϳ�ΪҼ�����ʮ�� �� rdn = 2 �ϳ�Ϊһ�������
	int ret = 0;
	char key = 0;

	//�û���¼
	ret = MSPLogin(NULL, NULL, login_configs);//��һ������Ϊ�û������ڶ�������Ϊ���룬�����������ǵ�¼�������û�����������Ҫ��http://open.voicecloud.cnע�Ტ��ȡappid
	if ( ret != MSP_SUCCESS )
	{
		printf("MSPLogin failed , Error code %d.\n",ret);
		goto exit ; //��¼ʧ�ܣ��˳���¼
	}
	//��Ƶ�ϳ�
	ret = text_to_speech(text,filename,param);//��Ƶ�ϳ�
	if ( ret != MSP_SUCCESS )
	{
		printf("text_to_speech: failed , Error code %d.\n",ret);
		goto exit ; //��¼ʧ�ܣ��˳���¼
	}
	exit:
	MSPLogout();//�˳���¼
	key = _getch();
	return 0;
}

