<?php
  $IP_Address = $_SERVER['REMOTE_ADDR'];

  $email = get_option( 'admin_email' );
  $subject = "SpruceGooseRecords.com FTP Uploader";
  $message = "IP Address: http://whatismyipaddress.com/ip/$IP_Address\n";
  $message .= "Time: " . date("D M j G:i:s T Y") . "\n\n\n";
  $message .= "This is an automatically generated email when somebody loads the page at www.sprucegooserecords.com/uploader/ftp";

  mail($email, $subject, $message);

?>    <font face="Arial, Helvetica, sans-serif" size="2">
	<script language="javascript" src="<? echo "/wp-content/plugins/artistography"; ?>/ftp/uftpscript.js"></script>
	<br/><br/>
  This software requires Java&trade; technology. <a href="http://www.java.com" target="_blank"><img src="/wp-content/plugins/artistography/ftp/images/get_java_green_button.gif" width="88" height="31" border="0"></a></font>