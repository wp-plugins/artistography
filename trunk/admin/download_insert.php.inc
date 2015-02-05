<?php

if ($_POST['do_choose'] && !strcmp($_POST['file'], "")) {
  _e("No file Chosen.<br/>\n", $i18n_domain);
}
else if ($_POST['do_choose']) {
  $file = $_POST['file'];

  $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_FILE_DOWNLOAD];
  $query = $wpdb->prepare("INSERT INTO $thetable (file_name, download_count)
            VALUES (%s, 0)", $file);
  $result = $wpdb->query($query);

  if($result === 0 || $result === FALSE) {
    wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $query) );
  } else {
    // successfully inserted file to upload
    printf( __("File added to the database: '%s'<br/>\n", $i18n_domain), $file);
  }

  echo '<center><form method="post" action=""><table><tr><td><input type="submit" value="';
  _e('Select A File To Add To Download Manager', $i18n_domain);
  echo '" name="do_select" /></td></tr></table></form></center>';
}
else if($_POST['do_select']) {
  $cmd = 'mv ' .$ftpuploader_path. '*.zip ' .$download_path;
  exec($cmd);
  $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_FILE_DOWNLOAD];
  $query = "SELECT *
            FROM   $thetable";
  $num = $wpdb->query($query);
  if($num === FALSE) {
    wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $query) );
  } else {
    // read files from DB
    for($i = 0; $i < $num; $i++) {
      $row = $wpdb->get_row($query, ARRAY_A, $i);
      $files_db[$i]['id'] = $row['id'];
      $files_db[$i]['file_name'] = $row['file_name'];
    }
    echo "<form method='post' action=''><table>";
     // read files from $download_path
     // don't display files if we already added them to the database
    if ($handle = opendir($download_path)) {
      while (false !== ($file = readdir($handle))) {
        if(!strcmp($file, ".") || !strcmp($file, "..")) continue;
        $found = false;
        for ($i = 0; $i < $num; $i++) {
          if(!strcmp($files_db[$i]['file_name'], $file)) {
            $id = $files_db[$i]['id'];
             // do not display
            $found = true;
          }
        }
        if($found != true && !is_dir($file)) {
           // is it already in the database, and is this a directory or a file?
          echo "<tr><td><input type='radio' name='file' value='$file' /></td><td>$file [" .round(((filesize($download_path . $file) / 1024) / 1024), 2). " MB]</td></tr>\n";
        }
      } // end while
      closedir($handle);
      echo '<tr><td></td><Td><input type="submit" value="';
      _e('Select File!', $i18n_domain);
      echo '" name="do_choose" /></td></tr></table></form>';
    }
  }
}
else {
  echo '<center><form method="post" action=""><table><tr><td><input type="submit" value="';
  _e('Select A File To Add To Download Manager', $i18n_domain);
  echo '" name="do_select" /></td></tr></table></form></center>';
}

?>