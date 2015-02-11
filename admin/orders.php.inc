<?php

GLOBAL $wpdb, $i18n_domain, $TABLE_NAME;

$orders = $wpdb->get_results("SELECT * FROM " .$wpdb->prefix.$TABLE_NAME[TABLE_ARTIST_ORDERS]);

/*<table>
	<thead>
		<th>#</td>
		<th>Forename</th>
		<th>Surname</th>
		<th>Email</th>
		<th>Address</th>
		<th>Products purchased</th>
		<th>User IP</th>
	</thead>
	<tbody>
		<tr>
			<td>ID</td>
			<td>Forename</td>
			<td>Surname</td>
			<td>Email</td>
			<td>Address</td>
			<td>Products purchased</td>
			<td>User IP</td>
		</tr>
	</tbody>
</table>
*/
?>
