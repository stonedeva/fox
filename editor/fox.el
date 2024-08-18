;; Vim editor syntax for Fox Language
(define-derived-mode fox-mode fundamental-mode "Fox"
  "Major mode for editing Fox language files."
  ;; Set the syntax highlighting
  (setq font-lock-defaults '((fox-font-lock-keywords)))
  ;; Set the mode name
  (setq mode-name "Fox"))

;; Define syntax highlighting rules
(defvar fox-font-lock-keywords
  '(;; Keywords
    ("\\<\\(if\\|else\\|while\\|for\\|return\\)\\>" . font-lock-keyword-face)
    ;; Constants
    ("\\<\\(true\\|false\\|null\\)\\>" . font-lock-constant-face)
    ;; Comments
    ("#.*" . font-lock-comment-face)
    ;; Strings
    ("\"[^\"]*\"" . font-lock-string-face)
    ;; Numbers
    ("\\b[0-9]+\\(?:\\.[0-9]*\\)?\\b" . font-lock-constant-face))
  "Font Lock keywords for `fox-mode'.")

;; Add mode to `auto-mode-alist` for automatic mode selection
(add-to-list 'auto-mode-alist '("\\.fox\\'" . fox-mode))

;; Provide the mode
(provide 'fox-mode)
