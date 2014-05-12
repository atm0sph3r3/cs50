<?
$user = User::getUser();
$portfolio = $user->portfolio();
while ($sale= current($results)) {
    print("<div>Sold ".key($results)." for a net income of ".numberFormat($sale));
    next($results);
}
?>
<div>Current cash balance: <?= numberFormat($user->cashBalance()) ?></div>
<div>Current portfolio balance: <?= numberFormat($portfolio["balance"]) ?></div>