<?php

GLOBAL $wpdb, $i18n_domain, $TABLE_NAME;

$orders = new Orders;
$i = 0;

echo "<table>
	<thead>
		<th>#</td>
		<th>Forename</th>
		<th>Surname</th>
		<th>Email</th>
		<th>Address</th>
		<th>Products purchased</th>
		<th>User IP</th>
	</thead>
	<tbody>";
	if ($orders->getTotalRows() > 0) {
		do {
		$products = unserialize($orders->itemsOrdered);
		echo "	<tr>
				<td>$orders->id</td>
				<td>$orders->forename</td>
				<td>$orders->surname</td>
				<td>$orders->email</td>
				<td>$orders->address_line_1, $orders->postcode, $orders->town</td>
				<td>";
		echo "			<ol>";
		for($j = 0; $j < count($products); $j++) {
			echo "			<li>" .$products[$j]. "</li>";
		}
		echo "			</ol>";
		echo	"	</td>
				<td>$orders->user_ip</td>
			</tr>";
		$orders->getNodeNext();
		$i++;
		} while($i<$orders->getTotalRows());
	} else {
		echo "<tr><td colspan='8'>There are no orders yet.</td></tr>";
	}
echo "	</tbody>
</table>";

?>
