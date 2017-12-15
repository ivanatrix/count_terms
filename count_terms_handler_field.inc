<?php

/**
 * Handler that allows rendering of fields to be links to the term pages.
 */
class count_terms_handler_field extends views_handler_field_numeric {
  /**
   * Constructor to provide additional field to add.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['tid'] = 'tid';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_term'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Provide link to term option
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to_term'] = array(
      '#title' => t('Link this field to its term'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_term']),
    );
  }

  /**
   * Render whatever the data is as a link to the term.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_term']) && $data !== NULL && $data !== '') {
      return l($data, 'taxonomy/term/' . $values->{$this->aliases['tid']}, array('html' => TRUE));
    }
    else {
      return $data;
    }
  }

  function render($values) {
  	$value = $values->{$this->field_alias};
    if (!empty($this->options['set_precision'])) {
      $value = number_format($value, $this->options['precision'], $this->options['decimal'], $this->options['separator']);
    }
    else {
      $remainder = abs($value) - intval(abs($value));
      $value = number_format(floor($value), 0, '', $this->options['separator']);
      if ($remainder) {
        // The substr may not be locale safe.
        $value .= $this->options['decimal'] . substr($remainder, 2);
      }
    }

    return $this->render_link(check_plain($this->options['prefix'] . $value . $this->options['suffix']), $values);
  }
}