<?php
    $artist = new Artist;
    $music = new Music;
//    $discography = new Discography;
    $track = new TrackList;

    echo "<h3>General</h3>\n";
?><table border='1'>
    <tr>
      <th></th>
      <th>Total</th>
      <th>Active</th>
      <th>Disabled</th>
    </tr>
    <tr>
      <td><?php
    _e("Artists", $i18n_domain);
?>    </td>
      <td><?php
    echo $artist->loadAll()->getTotalRows();
?>    </td>
      <td><?php
    echo $artist->loadAllEnabled()->getTotalRows();
?>    </td>
      <td><?php
    echo $artist->loadAllDisabled()->getTotalRows();
?>    </td>
    </tr>
    <tr>
      <td><?php
    _e("Albums", $i18n_domain);
?>    </td>
      <td><?php
    echo $music->loadAll()->getTotalRows();
?>    </td>
      <td><?php
    echo $music->loadAllEnabled()->getTotalRows();
?>    </td>
      <td><?php
    echo $music->loadAllDisabled()->getTotalRows();
?>    </td>
    </tr>
    <tr>
      <td><?php
    _e("Songs", $i18n_domain);
?>    </td>
      <td><?php
    echo $track->loadAll()->getTotalRows();
?>    </td>
      <td><?php
    echo $track->loadAllEnabled()->getTotalRows();
?>    </td>
      <td><?php
    echo $track->loadAllDisabled()->getTotalRows();
?>    </td>
    </tr>
  </table><?php

    unset($artist);
    unset($music);
//    unset($discography);
    unset($track);

?>