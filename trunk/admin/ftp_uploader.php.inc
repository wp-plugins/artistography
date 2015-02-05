<?php
  $IP_Address = $_SERVER['REMOTE_ADDR'];

  $email = get_option( 'admin_email' );
  $subject = __("FTP Uploader"", $i18n_domain);
  $message = __("IP Address", $i18n_domain). ": http://whatismyipaddress.com/ip/$IP_Address\n";
  $message .= __(""Time", $i18n_domain). ": " . date("D M j G:i:s T Y") . "\n\n\n";
  $message .= __("This is an automatically generated email.", $i18n_domain);

  mail($email, $subject, $message);

?>    <font face="Arial, Helvetica, sans-serif" size="2">
	<script language="javascript" src="<? echo "/wp-content/plugins/artistography"; ?>/ftp/uftpscript.js"></script>
	<br/><br/>
  <? _e("This software requires Java&trade; technology.", $i18n_domain); ?> <a href="http://www.java.com" target="_blank"><img src="/wp-content/plugins/artistography/ftp/images/get_java_green_button.gif" width="88" height="31" border="0"></a></font>
