// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
/**
 * @unrestricted
 */
Sources.AddSourceMapURLDialog = class extends UI.HBox {
  /**
   * @param {function(string)} callback
   */
  constructor(callback) {
    super(/* isWebComponent */ true);
    this.registerRequiredCSS('sources/dialog.css');
    this.contentElement.createChild('label').textContent = Common.UIString('Source map URL: ');

    this._input = UI.createInput('add-source-map', 'text');
    this._input.addEventListener('keydown', this._onKeyDown.bind(this), false);
    this.contentElement.appendChild(this._input);

    const addButton = UI.createTextButton(ls`Add`, this._apply.bind(this));
    this.contentElement.appendChild(addButton);

    this._dialog = new UI.Dialog();
    this._dialog.setSizeBehavior(UI.GlassPane.SizeBehavior.MeasureContent);
    this._dialog.setDefaultFocusedElement(this._input);

    /**
     * @this {Sources.AddSourceMapURLDialog}
     */
    this._done = function(value) {
      this._dialog.hide();
      callback(value);
    };
  }

  /**
   * @override
   */
  show() {
    super.show(this._dialog.contentElement);
    this._dialog.show();
  }

  _apply() {
    this._done(this._input.value);
  }

  /**
   * @param {!Event} event
   */
  _onKeyDown(event) {
    if (isEnterKey(event)) {
      event.consume(true);
      this._apply();
    }
  }
};
