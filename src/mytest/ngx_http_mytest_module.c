#include <ngx_config.h>    
#include <ngx_core.h>    
#include <ngx_http.h>    
  
 static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r);    
 static char *    ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);  
  
//����ģ�������ļ��Ĵ���  
static ngx_command_t ngx_http_mytest_commands[] = {    
    {  //����������  
        ngx_string("mytest"),  
    //���������ͣ������������Գ��ֵ�λ��  
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LMT_CONF|NGX_CONF_NOARGS,    
        //��������������ĺ��������������涨��  
    ngx_http_mytest,    
    //�������ļ��е�ƫ����  
        NGX_HTTP_LOC_CONF_OFFSET,  
    //Ԥ��Ľ�������������    
        0,    
    //�������ȡ��Ĵ�����  
        NULL    
    },    
    //command����Ҫ��ngx_null_command����  
    //#define ngx_null_command {ngx_null_string,0,NULL,0,0,NULL}  
    ngx_null_command    
 };    
  
  
 //mytestģ��������,��ΪNULL����˵��http��ܳ�ʼ��ʱû��ʲôҪ��    
 static ngx_http_module_t ngx_http_mytest_module_ctx = {    
    NULL,  //preconfiguration  
    NULL,  //postconfiguration  
    NULL,  //create main configuration  
    NULL,  //init main configuration  
    NULL,  //create server configuration  
    NULL,  //merge server configuration  
    NULL,  //create location configuration  
    NULL  //merge location configuration  
 };    
 //���Լ�mytestģ��Ķ��壬�ڱ���ʱ���뵽ȫ�ֵ�ngx_modules�����У�������Nginx��ʼ��ʱ�����ģ������г�ʼ���������������ngx_http_module_t���͵�ngx_http_mytest_module_ctx��  
    
 ngx_module_t ngx_http_mytest_module = {    
    NGX_MODULE_V1, //��Nginx����ĺ�����ʼ��ǰ�߸���Ա  
    &ngx_http_mytest_module_ctx,  //ģ��������Ľṹ�壬ָ���ض�ģ��Ĺ�������  
    ngx_http_mytest_commands,  //����������Ľṹ������  
    NGX_HTTP_MODULE,  //ģ������  
    //Nginx������ֹͣ�������߸�ִ�е�ĺ���ָ��  
    NULL,    
    NULL,    
    NULL,    
    NULL,    
    NULL,    
    NULL,    
    NULL,    
  
    NGX_MODULE_V1_PADDING  //��Nginx����ĺ궨��ʣ�µ�8�������ֶ�  
 };    
    
 //�������Ӧ�Ļص����������������г���mytest������ʱ�������������    
 static char *  ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)    
 {  //ckcf������ָ�ض���location���ڵ����ݽṹ����������mian��srv��loc�����������  
    //ÿ��http{},sever{},location{}����һ��ngx_http_core_loc_conf_t���͵����ݽṹ  
        ngx_http_core_loc_conf_t *clcf;    
      
    //�ҵ�mytest���������ڵ����ÿ�  
        clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);    
      
    //http����ڴ����û�������е�NGX_HTTP_CONTENT_PHASE�׶��ǣ�����������������URI�����������ڵ����ÿ���ƥ��ʱ���͵���  
    //clcf�е�handle���������������  
        //NGX_HTTP_CONTENT_PHASE���ڴ���http�������ݵĽ׶Σ����Ǵ󲿷�httpģ��ͨ������Ľ׶�  
    clcf->handler = ngx_http_mytest_handler;    
    
        return NGX_CONF_OK;    
 }    
      
  //ʵ����ɴ���Ļص�����    
  static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r)    
  {    
    //���󷽷�  
      if (!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD))) {    
          return NGX_HTTP_NOT_ALLOWED;    
      }    
    //����������İ��壬ֱ�Ӷ���������һ��Ҳ�ǲ���ʡ�Եģ����ǽ��ܰ����һ�ַ�����ֻ�����Ǽ򵥵Ķ�����  
    //��������ܣ��ͻ��˿��ܻ��ٴ���ͼ���Ͱ��壬�������������ܾͻ���ɿͻ��˷��ͳ�ʱ  
      ngx_int_t rc = ngx_http_discard_request_body(r);    
      if (rc != NGX_OK) {    
          return rc;    
      }    
    //������Ӧͷ��  
      ngx_str_t type = ngx_string("text/plain");    
      ngx_str_t response = ngx_string("hello world ! \n\rthis is my first Nginx module test ! ");    
      r->headers_out.status = NGX_HTTP_OK;    
      r->headers_out.content_length_n = response.len;    
      r->headers_out.content_type = type;    
    //����httpͷ��������Ҳ������Ӧ��  
      rc = ngx_http_send_header(r);    
      if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {    
          return rc;    
      }    
      
    ngx_buf_t *b;    
    //���������д������ڴ�ض��󣬴����ڴ�buf  
    b = ngx_create_temp_buf(r->pool, response.len);    
      if (b == NULL) {    
          return NGX_HTTP_INTERNAL_SERVER_ERROR;    
      }    
    //��Ч���ݴ�posλ�ÿ�ʼ������respon������  
      ngx_memcpy(b->pos, response.data, response.len);    
      //��Ч���ݵ�last����  
      b->last = b->pos + response.len;    
      //��Ϊngx_buf_t������ngx_chain_t������������last_buf���Ա���������һ�������Ļ��������򻯴���  
      b->last_buf = 1;    
  //���ڴ�buf����������������Ϊngx_http_output_filter�ĵ��������  
      ngx_chain_t out;    
      out.buf = b;    
    //����������һ��ngx_chain_t  
      out.next = NULL;    
      
      return ngx_http_output_filter(r, &out);    
  }   