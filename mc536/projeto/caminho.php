<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	if(!(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1))
		header('Location: login.php');

	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;
        $client = new Client();

    $run = "MATCH p=shortestPath((p1:Person)-[r:KNOWS*..15]-(p2:Person)) " .
"WHERE p1.usuario='{$_SESSION['usuario']}' and p2.usuario='{$_GET['usuario']}' " .
"return length(p) as tam, extract(n in filter(x in p WHERE has(x.nome)) | n.nome) as nomes";
    $query = new Cypher\Query($client, $run);
    $result = $query->getResultSet();
    if($result->count() > 0){
	    foreach($result as $row) {
	    	echo "Caminho: ";
	    	
	    	$first = true;

	    	foreach($row->offsetGet('nomes') as $nome){
	    		if(!$first){
	    			echo " -> ";
	    		}

	    		echo $nome;
	    		$first = false;
	    	}

	    	echo "<br>Tamamnho: " . $row->offsetGet('tam');
	    }
	} else {
		echo "Não há caminho entre os dois.";
	}
   ?>