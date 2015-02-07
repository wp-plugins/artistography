<?php

if (strcmp($_POST['save'], NULL)) {
  update_option('wp_artistography_preserve_database', ((!strcmp($_POST['preserve_database'], NULL)) ? true : false));
  update_option('wp_artistography_email_notify_ftp', ((!strcmp($_POST['email_notify_ftp'], NULL)) ? true : false));
  update_option('wp_artistography_ftp_host', $_POST['ftp_host']);
  update_option('wp_artistography_ftp_user', $_POST['ftp_user']);
  update_option('wp_artistography_ftp_pass', $_POST['ftp_pass']);
  update_option('wp_artistography_ftp_path', $_POST['ftp_path']);
  echo "Options saved.<br/>\n";
}

echo '<p>';
echo "<form method='post' action=''>";
    echo "<u><h3>" .__("General", $i18n_domain). "</h3></u>";
    echo "<input type='checkbox' name='preserve_database' id='preserve_databasae' checked='" .((get_option('wp_artistography_preserve_database')) ? 'checked' : ''). "' />" .__("Preserve Database (After Plugin Deletion)", $i18n_domain). "<br/>";
    echo "<input type='checkbox' name='email_notify_ftp' id='email_notify_ftp' checked='" .((get_option('wp_artistography_email_notify_ftp')) ? 'checked' : ''). "' />" .__("Email Notifications on FTP Uploader Page Load", $i18n_domain). "<br/>";
    echo "<u><h3>" .__("FTP Uploader", $i18n_domain). "</h3></u>";
    echo __("FTP Host", $i18n_domain) .": <input type='textbox' name='ftp_host' id='ftp_host' value='". get_option('wp_artistography_ftp_host') ."' /><br/>";
    echo __("FTP User", $i18n_domain) .": <input type='textbox' name='ftp_user' id='ftp_user' value='". get_option('wp_artistography_ftp_user') ."' /><br/>";
    echo __("FTP Pass", $i18n_domain) .": <input type='textbox' name='ftp_pass' id='ftp_pass' value='". get_option('wp_artistography_ftp_pass') ."' /><br/>";
    echo __("FTP Path", $i18n_domain) .": <input type='textbox' name='ftp_path' id='ftp_path' value='". get_option('wp_artistography_ftp_path') ."' /><br/>";
    echo "<input type='submit' name='save' id='save' value='" .__("Save", $i18n_domain). "' />";
echo '</form>';
echo '</p>';
?>
