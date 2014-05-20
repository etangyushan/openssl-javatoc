#include "detectorfun.h"

/* 显示证书信息 */
void show_certs (SSL *ssl)
{
	/* 验证双方的证书 */
	X509 *client_cert;
	client_cert = SSL_get_peer_certificate (ssl);
	if (client_cert != NULL)
	{
		DEBUG ("Client certificate\n");
		char *str = X509_NAME_oneline (X509_get_subject_name (client_cert), 0, 0);
		if (NULL == str)
		{
			DEBUG ("auth error\n");
			exit (1);
		}
		else
		{
			DEBUG ("subject: %s\n",str);
		}
		str = X509_NAME_oneline (X509_get_issuer_name (client_cert), 0, 0);
		if (NULL == str)
		{
			DEBUG ("certificate name is null\n");
			exit (1);
		}
		DEBUG ("issuer: %s\n", str);
		DEBUG ("connect successfully\n");
		X509_free (client_cert);
		OPENSSL_free (str);
	}
	else
	{
		DEBUG ("certificate invalid!\n");
		exit (1);
	}
}

/* 初始化ssl */
/* cipher为NULL是使用 "RC4-MD5" 加密器*/
SSL_CTX* openssl_init (char *cipher, char *cacert, char *mycertf, char *mykeyf)
{

	SSL_METHOD *meth;
	SSL_CTX *ctx;
	int seed_int[100] = {};
	int res,i;

	if (NULL == cipher)
	{
		cipher = "RC4-MD5";
	}

	DEBUG ("Begin OpenSSL init...\n");

	/* 初始化OpenSSL */
	SSL_library_init();

	/* 加载算法库 */
	OpenSSL_add_ssl_algorithms();

	/* 加载错误处理信息 */
	SSL_load_error_strings();

	/* 选择会话协议 */
	meth = (SSL_METHOD*)TLSv1_client_method(); 

	/* 创建会话环境 */
	ctx = SSL_CTX_new (meth);
	if (NULL == ctx)
	{
		DEBUG ("SSL_CTX_new fail\n");
		ERR_print_errors_fp (stderr);
		exit (1);
	}

	/* 制定证书验证方式 */
	SSL_CTX_set_verify (ctx, SSL_VERIFY_PEER, NULL);

	/* 为SSL会话加载CA证书 */
	SSL_CTX_load_verify_locations (ctx, cacert, NULL);

	/* 为SSL会话加载用户证书 */
	if (0 == SSL_CTX_use_certificate_file (ctx, mycertf, SSL_FILETYPE_PEM))
	{
		DEBUG ("SSL_CTX_use_certificate_file error\n");
		ERR_print_errors_fp (stderr);
		exit (1);
	}

	/* 为SSL会话加载用户私钥 */
	if (0 == SSL_CTX_use_PrivateKey_file (ctx, mykeyf, SSL_FILETYPE_PEM))
	{
		DEBUG ("SSL_CTX_use_PrivateKey_file error\n");
		ERR_print_errors_fp (stderr);
		exit (1);
	}
	DEBUG ("Verification private and certificate...\n");

	/* 验证私钥和证书是否相符 */
	if (!SSL_CTX_check_private_key (ctx))
	{
		DEBUG("Private key not match the certificate public key\n");
		exit (1);
	}
	DEBUG ("Private key is match the certificate\n");

	/* 设置随机数 */
	srand (time(0));
	for (i = 0; i < 100; i++)
	{
		seed_int[i] = rand();
	}
	RAND_seed (seed_int, sizeof (seed_int));

	/* 指定加密器类型 */
	res = SSL_CTX_set_cipher_list (ctx,cipher);
	if (0 == res)
	{
		DEBUG("SSL_CTX_set_cipher_list error\n");
		ERR_print_errors_fp (stderr);
		exit (1);
	}

	SSL_CTX_set_mode (ctx, SSL_MODE_AUTO_RETRY);

	DEBUG ("create SSL_CTX success\n");	

	return ctx;	
}

/* openssl和socket建立连接 */
SSL* openssl_socket (SSL_CTX* ctx, int sockfd)
{
	SSL *ssl;
	int res;

	DEBUG ("Begin openssl and socket connect...\n");

	/* 创建一个SSL套接字 */
	ssl = SSL_new (ctx);	
	if (NULL == ssl)
	{
		DEBUG ("SSL_NEW fail\n");
		ERR_print_errors_fp (stderr);
		exit (1);
	}

	/* 申请一个ssl套接字 */
	if (0 >= SSL_set_fd (ssl, sockfd))
	{
		DEBUG ("SSL_set_fd fail!\n");	
		ERR_print_errors_fp (stderr);
		exit (1);
	}

	/* 握手 */
	DEBUG ("Begin ssl_connect...\n");
	res = SSL_connect (ssl);
	if (0 >= res)
	{
		DEBUG ("SSL_connect fail!\n");
		ERR_print_errors_fp (stderr);
		exit (1);
	}

	DEBUG ("ssl_connect success\n");

	/* 显示证书信息 */
    show_certs (ssl);

	return ssl;

}
