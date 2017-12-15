<?php

/**
 * Implementation of hook_views_data().
 */
function count_terms_views_data() {
	$data = array();
	
	$data['count_terms']['table']['group'] = t('Taxonomy');
	$data['count_terms']['table']['join']['term_data'] = array(
		'left_field' => 'tid',
		'field' => 'tid'
	);
	$data['count_terms']['node_count'] = array(
		'field' => array(
			'handler' => 'count_terms_handler_field'
		),
		'filter' => array(
			'handler' => 'views_handler_filter_numeric'
		),
		'sort' => array(
			'handler' => 'views_handler_sort'
		)
	);
	$data['count_terms']['node_count']['title'] = t('Term Node Count');
	$data['count_terms']['node_count']['help'] = t('The number of nodes associated with this term');
	return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function count_terms_views_handlers() {
	return array(
		'handlers' => array(
			'count_terms_handler_field' => array(
				'parent' => 'views_handler_field_numeric'
			)
		)
	);
}