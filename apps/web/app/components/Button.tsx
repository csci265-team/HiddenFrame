/* eslint-disable react/prop-types */

import { Loader2 } from "lucide-react";
import { ButtonProps, Button as ShadcnButton } from "./ui/button";

export const Button: React.FC<ButtonProps> = (props) => {
    const { children, loading, disabled } = props;
    return (
        <ShadcnButton
            disabled={disabled || loading}
            className={`bg-colors-hf-brown text-colors-hf-beige dark:bg-colors-hf-beige dark:text-colors-hf-brown rounded-lg hover:bg-colors-hf-brown/90 dark:hover:bg-colors-hf-beige/90`}
            {...props} >
            {loading && <Loader2 className="mr-2 h-4 w-4 animate-spin" />}
            {children}
        </ShadcnButton>
    );
}